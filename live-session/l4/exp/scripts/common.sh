#!/usr/bin/env bash
#
# common.sh -- shared configuration and the run_experiment() driver used by
# every experiment script.  Source it; do not execute it directly.
#
set -euo pipefail

# --- paths ------------------------------------------------------------------
COMMON_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$COMMON_DIR/.." && pwd)"
BIN_DIR="$ROOT_DIR/bin"
RESULTS_DIR="$ROOT_DIR/results"

# --- tunables (override via environment) ------------------------------------
MAIN_DURATION="${MAIN_DURATION:-30}"   # total runtime of the main job (s)
BURST_START="${BURST_START:-10}"       # delay before the burst starts (s)
BURST_DURATION="${BURST_DURATION:-10}" # how long the burst runs (s)
NUM_BURST="${NUM_BURST:-8}"            # number of burst processes
PIN_CPU="${PIN_CPU:-0}"               # CPU the main job is pinned to

# --- helpers ----------------------------------------------------------------
have_taskset() { command -v taskset >/dev/null 2>&1; }
epoch()        { date +%s.%N; }
delta()        { awk -v a="$1" -v b="$2" 'BEGIN { printf "%.3f", b - a }'; }

ensure_built() {
    if [[ ! -x "$BIN_DIR/cpu_job" || ! -x "$BIN_DIR/io_job" || ! -x "$BIN_DIR/burst" ]]; then
        echo "[common] building binaries..."
        make -C "$ROOT_DIR"
    fi
}

# run_experiment <name> <cpu|io> <burst_pin 0|1> <burst_nice|"">
#
# Starts the main job (always pinned to PIN_CPU for a reproducible baseline),
# waits BURST_START seconds, launches NUM_BURST burst processes for
# BURST_DURATION seconds, then lets the main job finish.  Writes a latency CSV
# and a metadata file recording the measured burst interval, and renders a
# plot if python3 is available.
run_experiment() {
    local name="$1"
    local main_kind="$2"
    local burst_pin="$3"
    local burst_nice="$4"

    ensure_built
    mkdir -p "$RESULTS_DIR"

    local latency_csv="$RESULTS_DIR/${name}_latency.csv"
    local meta="$RESULTS_DIR/${name}_meta.env"
    local scratch="$RESULTS_DIR/${name}_scratch.dat"

    # The main job is always pinned to one CPU so contention is reproducible.
    local main_pin=()
    if have_taskset; then
        main_pin=(taskset -c "$PIN_CPU")
    else
        echo "[$name] warning: taskset not found; main job not pinned"
    fi

    echo "[$name] main '$main_kind' job: ${MAIN_DURATION}s, pinned to CPU $PIN_CPU"
    local t0
    t0="$(epoch)"
    if [[ "$main_kind" == "io" ]]; then
        "${main_pin[@]}" "$BIN_DIR/io_job" "$MAIN_DURATION" "$latency_csv" "$scratch" &
    else
        "${main_pin[@]}" "$BIN_DIR/cpu_job" "$MAIN_DURATION" "$latency_csv" &
    fi
    local main_pid=$!

    # Wait, then unleash the burst.
    sleep "$BURST_START"

    # Build the burst command prefix (pinning / priority).
    local pin_prefix=()
    if [[ "$burst_pin" == "1" ]]; then
        if have_taskset; then
            pin_prefix=(taskset -c "$PIN_CPU")
        else
            echo "[$name] warning: taskset not found; burst not pinned"
        fi
    fi

    local nice_prefix=()
    if [[ -n "$burst_nice" ]]; then
        if [[ "$burst_nice" -lt 0 && $EUID -ne 0 ]]; then
            if command -v sudo >/dev/null 2>&1; then
                echo "[$name] note: negative nice needs privileges; using sudo (may prompt)"
                nice_prefix=(sudo nice -n "$burst_nice")
            else
                echo "[$name] warning: negative nice without root/sudo will likely fail"
                nice_prefix=(nice -n "$burst_nice")
            fi
        else
            nice_prefix=(nice -n "$burst_nice")
        fi
    fi

    echo "[$name] launching $NUM_BURST burst jobs (pin=$burst_pin nice=${burst_nice:-none})"
    local burst_pids=()
    local bstart
    bstart="$(delta "$t0" "$(epoch)")"
    local i
    for ((i = 0; i < NUM_BURST; i++)); do
        "${pin_prefix[@]}" "${nice_prefix[@]}" "$BIN_DIR/burst" "$BURST_DURATION" &
        burst_pids+=($!)
    done

    # Burst processes self-terminate after BURST_DURATION.
    wait "${burst_pids[@]}"
    local bend
    bend="$(delta "$t0" "$(epoch)")"
    echo "[$name] burst finished (interval ${bstart}s .. ${bend}s)"

    # Let the main job run out its remaining time.
    wait "$main_pid"
    echo "[$name] main job done -> $latency_csv"

    cat > "$meta" <<EOF
EXP_NAME=$name
MAIN_KIND=$main_kind
BURST_START_S=$bstart
BURST_END_S=$bend
NUM_BURST=$NUM_BURST
BURST_PIN=$burst_pin
BURST_NICE=${burst_nice:-}
EOF

    if command -v python3 >/dev/null 2>&1; then
        python3 "$ROOT_DIR/plot.py" "$latency_csv" --meta "$meta" \
            -o "$RESULTS_DIR/${name}.png" --title "$name" \
            || echo "[$name] plot step skipped/failed (is matplotlib installed?)"
    else
        echo "[$name] python3 not found; skipping plot"
    fi
}
