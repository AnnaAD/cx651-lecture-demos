#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#define FILEPATH "song.txt"
#define FILESIZE 100

int main(int argc, char *argv[])
{
    int i;
    int fd;
    char *map;  /* mmapped array of int's */

    /* Open a file for writing.
     *  - Creating the file if it doesn't exist.
     *  - Truncating it to 0 size if it already exists. (not really needed)
     *
     * Note: "O_WRONLY" mode is not sufficient when mmaping.
     */
    fd = open(FILEPATH, O_RDWR, (mode_t)0600);
    if (fd == -1) {
	perror("Error opening file for writing");
	exit(EXIT_FAILURE);
    }

    printf("Have not yet mmapped! Press enter to mmap.\n");
    getchar();
    
    /* Now the file is ready to be mmapped.*/
    map = mmap(0, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
	close(fd);
	perror("Error mmapping the file");
	exit(EXIT_FAILURE);
    }
    
    /* Now write int's to the file as if it were memory (an array of ints).*/
    for (i = 0; i < FILESIZE; ++i) {
      if(map[i] == 'a') {
	map[i] = 'A';
      }
    }

    printf("mmap complete! Press enter to finish.\n");
    getchar();

    /* Don't forget to free the mmapped memory */
    if (munmap(map, FILESIZE) == -1) {
	perror("Error un-mmapping the file");
    }

    close(fd);
    return 0;
}
