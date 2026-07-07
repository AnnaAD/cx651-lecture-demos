#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_POSTS 100
#define MAX_MESSAGE_LEN 256

char message_board[MAX_POSTS][MAX_MESSAGE_LEN];
int num_posts = 0;

void add_post(const char *msg) {
    if (num_posts >= MAX_POSTS)
        return; // Board full

    strncpy(message_board[num_posts], msg, MAX_MESSAGE_LEN - 1);
    message_board[num_posts][MAX_MESSAGE_LEN - 1] = '\0';
    num_posts++;
}

void send_board(int client) {
    char buffer[BUFFER_SIZE * 4];
    buffer[0] = '\0';

    for (int i = 0; i < num_posts; i++) {
        strcat(buffer, message_board[i]);
        strcat(buffer, "\n");
    }

    send(client, buffer, strlen(buffer), 0);
}

int main() {
    int server_fd, client_fd;
    struct sockaddr_in addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        client_fd = accept(server_fd, NULL, NULL);

        char buffer[BUFFER_SIZE];

        int n = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);

        if (n > 0) {
            buffer[n] = '\0';

            // Remove trailing newline
            buffer[strcspn(buffer, "\r\n")] = '\0';

            printf("Received: %s\n", buffer);

            add_post(buffer);

            send_board(client_fd);
        }

        close(client_fd);
    }

    close(server_fd);
    return 0;
}