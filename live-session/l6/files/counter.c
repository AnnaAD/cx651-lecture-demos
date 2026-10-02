#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 20000000L

int T;
long count;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void *work(void *a) {
    for (long i = 0; i < N / T; i++) {
        pthread_mutex_lock(&m);
        count++;
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main(int argc, char **argv) {
    T = atoi(argv[1]);
    pthread_t t[64];
    for (long i = 0; i < T; i++) pthread_create(&t[i], NULL, work, NULL);
    for (long i = 0; i < T; i++) pthread_join(t[i], NULL);
    printf("%ld\n", count);
}
