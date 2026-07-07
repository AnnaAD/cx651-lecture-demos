#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int sock;
    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    char message[256];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    send(sock, message, strlen(message), 0);

    char board[BUFFER_SIZE];

    int n = recv(sock, board, BUFFER_SIZE - 1, 0);

    if (n > 0) {
        board[n] = '\0';

        printf("\nCurrent Message Board\n");
        printf("---------------------\n");
        printf("%s", board);
    }

    close(sock);

    return 0;
}