#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 400000000L

int T;
double sums[64];

void *work(void *a) {
    long id = (long)a;
    double s = 0;
    for (long i = id; i < N; i += T) {
        double x = (i + 0.5) / N;
        s += 4.0 / (1.0 + x * x);
    }
    sums[id] = s;
    return NULL;
}

int main(int argc, char **argv) {
    T = atoi(argv[1]);
    pthread_t t[64];
    for (long i = 0; i < T; i++) pthread_create(&t[i], NULL, work, (void *)i);
    double pi = 0;
    for (long i = 0; i < T; i++) {
        pthread_join(t[i], NULL);
        pi += sums[i];
    }
    printf("%f\n", pi / N);
}
