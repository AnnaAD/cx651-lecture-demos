#include <stdlib.h>
#include <stdio.h>

int print_numbers(void) {
  int* arr = malloc(sizeof(int)*100000);

  if(arr == NULL) {
    printf("Malloc FAILED\n");
    exit(1);
  }

  for(int i = 0; i < 30; i++) {
    arr[i] = i*3;
  }

  for(int i = 0; i < 30; i++) {
    printf("%d ", *(arr + i));
  }
  printf("\n");
  return 0;
}

int main(void) {
  while(1) {
    print_numbers();
  }
}
