#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 4000000
int nt;
long sums[64];

char *to_str(long n) {
    static char buf[32];
    snprintf(buf, sizeof buf, "%ld", n);
    return buf;
}

long digit_sum(long lo, long hi) {
    long s = 0;
    for (long n = lo; n < hi; n++)
        for (char *p = to_str(n); *p; p++) s += *p - '0';
    return s;
}

void *work(void *arg) {
    long id = (long)arg;
    sums[id] = digit_sum(id * N / nt, (id + 1) * N / nt);
    return NULL;
}

int main(int argc, char **argv) {
    nt = argc > 1 ? atoi(argv[1]) : 4;
    pthread_t t[64];
    long expect = digit_sum(0, N), total = 0;
    for (long i = 0; i < nt; i++) pthread_create(&t[i], NULL, work, (void *)i);
    for (int i = 0; i < nt; i++) {
        pthread_join(t[i], NULL);
        total += sums[i];
    }
    printf("expected %ld got %ld\n", expect, total);
}
