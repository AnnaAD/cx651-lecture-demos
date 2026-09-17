#!/usr/bin/env bash
# Experiment 1-2: the burst is pinned to the SAME CPU as the main job with
# taskset, forcing direct contention on one core.
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

run_experiment "exp1-2" cpu 1 ""
