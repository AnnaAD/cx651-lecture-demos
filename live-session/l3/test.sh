#!/bin/bash

mkdir -p data

for program in matmul-*; do
    if [[ -x "$program" ]]; then
        echo "Running $program..."
        valgrind --tool=cachegrind --cache-sim=yes "./$program" \
            > "data/$program.txt" 2>&1
    fi
done
