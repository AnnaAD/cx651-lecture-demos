#include <stdio.h>

int main(void) {
    int factors = 0;
    long long num = 512346137;
    for (long long i = 2; i < num; ++i) {
        if (num % i == 0) {
            factors ++;
        }
    }

    if(factors == 0) {
        printf("prime!\n");
    } else {
      printf("factors = %d\n", factors);
    }

}