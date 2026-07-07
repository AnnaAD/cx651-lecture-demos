#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000000

int main(void) {
  int* A = malloc(sizeof(int) * SIZE);
  
  for(int i = 0; i < SIZE; i++) {
    A[i] = rand() + rand();
  }

  int sum = 0;
  for(int i = 0; i < SIZE; i++) {
    sum += rand() + A[i];
  }

  printf("sum: %d\n", sum);
  free(A);
}