#include <stdio.h>

int main(void) {
  int x = 6;
  int *ptr = &x;

  int y = *(ptr+10000000);

  printf("%d %p %d\n", x, ptr, y);
}
