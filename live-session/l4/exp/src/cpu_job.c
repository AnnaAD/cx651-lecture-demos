/*
 * cpu_job -- CPU-intensive "main" job that periodically reports task latency.
 *
 * The job repeatedly performs a FIXED chunk of arithmetic ("a task") and
 * records how long that chunk took in wall-clock time.  When the CPU is
 * uncontended the latency is stable; when other processes compete for the
 * same core the fixed chunk takes longer, so the reported latency rises.
 *
 * Output is a CSV with a header line: "time_s,latency_ms" where time_s is
 * the number of seconds since the job started (a monotonic clock) and
 * latency_ms is the wall-clock time taken to complete one task.
 *
 * usage: cpu_job <duration_s> <output_csv> [work_iters]
 */
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double now_s(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

/* volatile sink so the optimizer cannot delete the busy loop */
static volatile double sink;

/* One "task": a fixed amount of floating-point work. */
static double do_task(long work)
{
    double acc = 0.0;
    for (long i = 0; i < work; i++) {
        acc += (double)i * 1.0000001;
        acc -= (double)(long)acc; /* keep the value bounded */
    }
    return acc;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s <duration_s> <output_csv> [work_iters]\n",
                argv[0]);
        return 1;
    }

    double duration = atof(argv[1]);
    const char *out = argv[2];
    long work = (argc > 3) ? atol(argv[3]) : 2000000L;

    FILE *f = fopen(out, "w");
    if (!f) {
        perror("fopen");
        return 1;
    }
    fprintf(f, "time_s,latency_ms\n");

    double start = now_s();
    double t = start;
    while (t - start < duration) {
        double task_start = now_s();
        sink = do_task(work);
        double task_end = now_s();

        double latency_ms = (task_end - task_start) * 1000.0;
        fprintf(f, "%.6f,%.4f\n", task_end - start, latency_ms);
        fflush(f);
        t = task_end;
    }

    fclose(f);
    return 0;
}
