#!/usr/bin/env bash
# Build everything and run every experiment in sequence.
set -euo pipefail
HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

make -C "$HERE/.."
for e in exp1-1 exp1-2 exp1-3 exp1-4 exp2; do
    echo "=================================================================="
    echo " Running $e"
    echo "=================================================================="
    bash "$HERE/$e.sh"
done
echo "All experiments complete. See the results/ directory for CSVs and PNGs."
