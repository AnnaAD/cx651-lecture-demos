/*
 * burst -- a CPU-bound "noise" process.
 *
 * It simply spins doing arithmetic for a fixed number of seconds and then
 * exits.  A group of these is launched to create a burst of CPU contention
 * for the main job.
 *
 * usage: burst [duration_s]   (default 10s)
 */
#define _POSIX_C_SOURCE 199309L
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

int main(int argc, char **argv)
{
    double duration = (argc > 1) ? atof(argv[1]) : 10.0;

    double start = now_s();
    double acc = 0.0;
    while (now_s() - start < duration) {
        for (long i = 0; i < 1000000L; i++) {
            acc += (double)i * 1.0000001;
            acc -= (double)(long)acc;
        }
        sink = acc;
    }
    return 0;
}
