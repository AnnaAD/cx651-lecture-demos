perf stat -e dTLB-loads,dTLB-load-misses ./tlb-okay1
perf stat -e dTLB-loads,dTLB-load-misses ./tlb-okay2
perf stat -e dTLB-loads,dTLB-load-misses ./tlb-misser
