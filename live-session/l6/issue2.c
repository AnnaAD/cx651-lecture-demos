#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 20000000
int nt;
long partial[64];

void *work(void *arg) {
    int id = *(int *)arg;
    long s = 0;
    for (long i = id; i < N; i += nt) s += i % 7;
    partial[id] = s;
    return NULL;
}

int main(int argc, char **argv) {
    nt = argc > 1 ? atoi(argv[1]) : 4;
    pthread_t t[64];
    long expect = 0, total = 0;
    for (long i = 0; i < N; i++) expect += i % 7;
    for (int i = 0; i < nt; i++) pthread_create(&t[i], NULL, work, &i);
    for (int i = 0; i < nt; i++) {
        pthread_join(t[i], NULL);
        total += partial[i];
    }
    printf("expected %ld got %ld\n", expect, total);
}
