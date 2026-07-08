#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define MAX_POSTS 100
#define MAX_MESSAGE_LEN 256
#define BUFFER_SIZE 4096

char message_board[MAX_POSTS][MAX_MESSAGE_LEN];
int num_posts = 0;

int main() {
    int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr, client_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Message board server listening on port %d\n", PORT);

    while (1) {
        char buffer[MAX_MESSAGE_LEN];

        socklen_t client_len = sizeof(client_addr);

        ssize_t bytes = recvfrom(sock_fd,
                                 buffer,
                                 sizeof(buffer) - 1,
                                 0,
                                 (struct sockaddr *)&client_addr,
                                 &client_len);

        buffer[bytes] = '\0';

        buffer[strcspn(buffer, "\r\n")] = '\0';

        printf("Received: %s\n", buffer);

        if (num_posts < MAX_POSTS) {
            strcpy(message_board[num_posts], buffer);
            num_posts++;
        }

        char reply[BUFFER_SIZE];
        reply[0] = '\0';

        for (int i = 0; i < num_posts; i++) {
            strcat(reply, message_board[i]);
            strcat(reply, "\n");
        }

        sendto(sock_fd,
               reply,
               strlen(reply),
               0,
               (struct sockaddr *)&client_addr,
               client_len);
    }

    close(sock_fd);

    return 0;
}