#!/usr/bin/env bash
# Experiment 1-4: the burst shares the main job's CPU but runs at HIGHER
# priority (nice -10).  Negative niceness needs root, so this script may use
# sudo (and prompt for a password).
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

run_experiment "exp1-4b" cpu 0 "-10"
