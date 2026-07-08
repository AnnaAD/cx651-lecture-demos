import subprocess
import sys
import time

if len(sys.argv) != 2:
    print(f"Usage: python3 {sys.argv[0]} <num_clients>")
    sys.exit(1)

N = int(sys.argv[1])

total = 0.0

for i in range(1, N + 1):
    start = time.perf_counter()

    subprocess.run(
        ["./client"],
        input=f"Message {i}\n",
        text=True,
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )

    elapsed = time.perf_counter() - start
    total += elapsed

    print(f"Client {i}: {elapsed:.6f} seconds")

print(f"\nAverage response time: {total / N:.6f} seconds")