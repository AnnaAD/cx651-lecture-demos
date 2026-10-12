#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define N 2

struct request {
  int A[N * N];
  int B[N * N];
};

struct response {
  int C[N * N];
};

struct job {
  struct request req;
  struct sockaddr_in client_addr;
  socklen_t client_len;
};

int sock_fd;

void *handle(void *arg) {
    struct job *job = arg;
    struct response res = {0};

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                res.C[i * N + j] += job->req.A[i * N + k] * job->req.B[k * N + j];

    sendto(sock_fd, &res, sizeof(res), 0, (struct sockaddr *)&job->client_addr, job->client_len);
    free(job);
    return NULL;
}

int main() {
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr = {0};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Server listening on port 8080\n");

    while (1) {
        struct job *job = malloc(sizeof(*job));
        job->client_len = sizeof(job->client_addr);

        recvfrom(sock_fd, &job->req, sizeof(job->req), 0, (struct sockaddr *)&job->client_addr, &job->client_len);

        pthread_t tid;
        pthread_create(&tid, NULL, handle, job);
        pthread_detach(tid);
    }

    close(sock_fd);
    return 0;
}
