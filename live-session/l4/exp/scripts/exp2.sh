#!/usr/bin/env bash
# Experiment 2: an I/O-bound main job + a burst of CPU-bound processes
# (default scheduling).
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

run_experiment "exp2" io 0 ""
