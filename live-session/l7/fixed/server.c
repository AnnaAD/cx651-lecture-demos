#include <stdio.h>
#include <unistd.h>
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

int main() {
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr = {0}, client_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Server listening on port 8080\n");

    while (1) {
        struct request req;
        struct response res = {0};
        socklen_t client_len = sizeof(client_addr);

        ssize_t bytes = recvfrom(sock_fd, &req, sizeof(req), 0, (struct sockaddr *)&client_addr, &client_len);
        printf("Received %zd bytes\n", bytes);

        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                for (int k = 0; k < N; k++)
                    res.C[i * N + j] += req.A[i * N + k] * req.B[k * N + j];

        sendto(sock_fd, &res, sizeof(res), 0, (struct sockaddr *)&client_addr, client_len);
    }

    close(sock_fd);
    return 0;
}
