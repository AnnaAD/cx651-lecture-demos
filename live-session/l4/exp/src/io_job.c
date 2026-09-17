/*
 * io_job -- I/O-bound "main" job that periodically reports task latency.
 *
 * Each "task" writes a block to a scratch file and fsync()s it to storage,
 * then measures how long the write+fsync took.  The job spends most of its
 * time blocked in I/O (so it is I/O bound), but it still needs the CPU to
 * issue each request and to run again after the I/O completes.  When a burst
 * of CPU-bound processes competes for the core, the I/O job is scheduled
 * less promptly and the reported latency rises.
 *
 * Output CSV header: "time_s,latency_ms".
 *
 * usage: io_job <duration_s> <output_csv> [scratch_file] [block_bytes]
 */
#define _XOPEN_SOURCE 700
#ifdef __APPLE__
#define _DARWIN_C_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

static double now_s(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr,
                "usage: %s <duration_s> <output_csv> [scratch_file] [block_bytes]\n",
                argv[0]);
        return 1;
    }

    double duration = atof(argv[1]);
    const char *out = argv[2];
    const char *scratch = (argc > 3) ? argv[3] : "io_scratch.dat";
    size_t block = (argc > 4) ? (size_t)atol(argv[4]) : (size_t)(64 * 1024);

    char *buf = malloc(block);
    if (!buf) {
        perror("malloc");
        return 1;
    }
    memset(buf, 0xAB, block);

    FILE *f = fopen(out, "w");
    if (!f) {
        perror("fopen");
        free(buf);
        return 1;
    }
    fprintf(f, "time_s,latency_ms\n");

    double start = now_s();
    double t = start;
    while (t - start < duration) {
        double task_start = now_s();

        int fd = open(scratch, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("open");
            break;
        }
        ssize_t w = write(fd, buf, block);
        if (w < 0)
            perror("write");
        fsync(fd);
        close(fd);

        double task_end = now_s();
        double latency_ms = (task_end - task_start) * 1000.0;
        fprintf(f, "%.6f,%.4f\n", task_end - start, latency_ms);
        fflush(f);
        t = task_end;
    }

    unlink(scratch);
    free(buf);
    fclose(f);
    return 0;
}
