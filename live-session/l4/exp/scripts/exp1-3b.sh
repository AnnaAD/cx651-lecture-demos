#!/usr/bin/env bash
# Experiment 1-3: the burst shares the main job's CPU but runs at LOWER
# priority (nice +19), so the scheduler should favour the main job.
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

run_experiment "exp1-3b" cpu 0 "19"
