#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define N 2
#define WORKERS 4

struct request {
  int A[N * N];
  int B[N * N];
};

struct response {
  int C[N * N];
};

int sock_fd;

void *worker(void *arg) {
    while (1) {
        struct request req;
        struct response res = {0};
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);

        recvfrom(sock_fd, &req, sizeof(req), 0, (struct sockaddr *)&client_addr, &client_len);
        printf("Worker %ld handling request\n", (long)arg);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    res.C[i * N + j] += req.A[i * N + k] * req.B[k * N + j];

        sendto(sock_fd, &res, sizeof(res), 0, (struct sockaddr *)&client_addr, client_len);
    }
    return NULL;
}

int main() {
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Server listening on port 8080 with %d workers\n", WORKERS);

    pthread_t tids[WORKERS];
    for (long i = 0; i < WORKERS; i++) pthread_create(&tids[i], NULL, worker, (void *)i);
    for (int i = 0; i < WORKERS; i++) pthread_join(tids[i], NULL);

    close(sock_fd);
    return 0;
}
