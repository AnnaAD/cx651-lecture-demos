#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>


int main() {
   char *large_array = malloc(1024*1024*1024); // 1GB allocated
    
    if (large_array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    // Access memory constantly, random pages.
    for (int i = 0; i < 10000000; i++) {
        int random_index = rand() % (1024 * 1024 * 1024); // Access random locations in the array
        volatile int value = large_array[random_index]; // Read value from the random location 
        // (Do something with value)
	    large_array[random_index] = random_index * 2;
    }
    
    free(large_array);
    return 0;
}
