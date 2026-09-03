#include <stdio.h>

int mul(long long temp, long long iters) {
  if(iters == 0) {
    return 0;
  }
  return temp + mul(temp, iters-1);
}

int main(void) {
  long long final = mul(3,3);
  printf("final: %lld\n", final);
}

