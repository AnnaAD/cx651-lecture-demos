

# Experiment 1-1
Start up a CPU intensive job that is regularily reporting latency of tasks
Add in a burst of other processes after a small time.

# Experiment 1-2
The burst of other processes are scheduled to the same CPU with taskset

# Experiment 1-3
The burst of other processes are scheduled with a lower priority via `nice`
# Experiment 1-4
The burst of other processes are scheduled higher priority

# Experiment 2
Start up an I/O bound task that is reporting latency of task
Add in a burst of other CPU-bound processes after a small time.

# Create and Plotting Script
- Plot the latency of the main job (not the burst) over time. Include the time where the interval of burst jobs starts and ends.
