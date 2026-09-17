#!/usr/bin/env python3
"""
plot.py -- plot the main job's task latency over time and shade the interval
during which the burst of other processes was running.

usage:
    python3 plot.py <latency_csv> [--meta <meta.env>] [-o out.png] [--title T]

The latency CSV must have a header "time_s,latency_ms".  The optional meta
file (written by the experiment scripts) provides BURST_START_S / BURST_END_S
so the burst interval can be marked on the plot.
"""
import argparse
import csv
import os
import sys


def load_csv(path):
    times, lats = [], []
    with open(path, newline="") as fh:
        reader = csv.DictReader(fh)
        for row in reader:
            try:
                times.append(float(row["time_s"]))
                lats.append(float(row["latency_ms"]))
            except (KeyError, ValueError):
                continue
    return times, lats


def load_meta(path):
    meta = {}
    if not path or not os.path.exists(path):
        return meta
    with open(path) as fh:
        for line in fh:
            line = line.strip()
            if not line or line.startswith("#") or "=" not in line:
                continue
            key, val = line.split("=", 1)
            meta[key.strip()] = val.strip()
    return meta


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("latency_csv", help="CSV with columns time_s,latency_ms")
    ap.add_argument("--meta", help="meta.env file with BURST_START_S/BURST_END_S")
    ap.add_argument("-o", "--out", help="output image path (default: <csv>.png)")
    ap.add_argument("--title", help="plot title")
    args = ap.parse_args()

    times, lats = load_csv(args.latency_csv)
    if not times:
        sys.exit(f"no data points found in {args.latency_csv}")

    meta = load_meta(args.meta)

    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    fig, ax = plt.subplots(figsize=(10, 5))
    ax.plot(times, lats, lw=1.0, color="#1f77b4", label="main job task latency")

    # Shade the burst interval if we know it.
    def fnum(key):
        try:
            return float(meta[key])
        except (KeyError, ValueError):
            return None

    b0, b1 = fnum("BURST_START_S"), fnum("BURST_END_S")
    if b0 is not None and b1 is not None:
        ax.axvspan(b0, b1, color="#d62728", alpha=0.12, label="burst active")
        ax.axvline(b0, color="#d62728", ls="--", lw=1.0)
        ax.axvline(b1, color="#d62728", ls="--", lw=1.0)

    ax.set_xlabel("time since job start (s)")
    ax.set_ylabel("task latency (ms)")
    title = args.title or meta.get("EXP_NAME") or os.path.basename(args.latency_csv)
    nburst = meta.get("NUM_BURST")
    if nburst:
        title = f"{title}  (burst = {nburst} procs)"
    ax.set_title(title)
    ax.grid(True, alpha=0.3)
    ax.legend(loc="upper right")
    fig.tight_layout()

    out = args.out or (os.path.splitext(args.latency_csv)[0] + ".png")
    fig.savefig(out, dpi=120)
    print(f"wrote {out}")


if __name__ == "__main__":
    main()
