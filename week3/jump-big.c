#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000000

int main(void) {
  int* A = malloc(sizeof(int) * SIZE);
  
  for(int i = 0; i < SIZE; i++) {
    A[rand() % SIZE] = rand();
  }

  int sum = 0;
  for(int i = 0; i < SIZE; i++) {
    sum += A[rand() % SIZE];
  }

  printf("sum: %d\n", sum);
  free(A);
}