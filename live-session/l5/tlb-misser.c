#include <stdio.h>
#include <stdlib.h>

int main() {
    char *large_array = malloc(1024 * 1024 * 10);
    
    if (large_array == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
    
    for (int i = 0; i < 1000000; i++) {
        int random_index = rand() % (1024 * 1024 * 10);
        volatile int value = large_array[random_index]; 
	large_array[random_index] = value * 2;
    }
    
    free(large_array);
    return 0;
}
