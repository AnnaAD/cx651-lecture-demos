#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {

    for(int i = 0; i < 1000000; i++) {
        char buffer[100];
        int fd, bytesRead;

        // Open a file using the open system call
        fd = open("example.txt", O_RDONLY);
        if (fd == -1) {
            perror("open");
            return 1;
        }

        // Read from the file using the read system call
        bytesRead = read(fd, buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("read");
            return 1;
        }

        // Write to standard output using the write system call
        //write(STDOUT_FILENO, buffer, bytesRead);

        // Close the file using the close system call
        close(fd);
    }

    return 0;
}