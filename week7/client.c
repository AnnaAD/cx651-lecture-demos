#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    char message[256];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    sendto(sock_fd,
           message,
           strlen(message),
           0,
           (struct sockaddr *)&server_addr,
           sizeof(server_addr));

    char buffer[BUFFER_SIZE];

    socklen_t server_len = sizeof(server_addr);

    ssize_t bytes = recvfrom(sock_fd,
                             buffer,
                             sizeof(buffer) - 1,
                             0,
                             (struct sockaddr *)&server_addr,
                             &server_len);

    buffer[bytes] = '\0';

    printf("\nCurrent Message Board\n");
    printf("---------------------\n");
    printf("%s", buffer);

    close(sock_fd);

    return 0;
}