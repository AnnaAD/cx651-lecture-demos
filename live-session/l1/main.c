#include <stdio.h>

extern long long mystery(long long a);

int main(void) {
  printf("m(12) = %lld, m(4) = %lld\n", mystery(12), mystery(4));
}