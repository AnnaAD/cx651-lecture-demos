#!/usr/bin/env bash
# Experiment 1-1: CPU-intensive main job + a burst of other processes using
# the default scheduler (burst not pinned, normal priority).
set -euo pipefail
source "$(dirname "${BASH_SOURCE[0]}")/common.sh"

run_experiment "exp1-1" cpu 0 ""
