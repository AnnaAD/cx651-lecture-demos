#!/bin/bash
gcc -O2 -pthread pi.c -o pi
gcc -O2 -pthread counter.c -o counter
MAX=${1:-$(nproc)}
echo "program,threads,seconds" > timings.csv
for p in pi counter; do
  for n in $(seq 1 $MAX); do
    s=$(date +%s.%N)
    taskset -c 0-$((n-1)) ./$p $n > /dev/null
    e=$(date +%s.%N)
    echo "$p,$n,$(echo "$e - $s" | bc)" >> timings.csv
  done
done
