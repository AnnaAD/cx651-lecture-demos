#include <stdio.h>
#include <stdlib.h>

void matrix_multiply(int *mat1, int *mat2, int *result, int rows1, int cols1, int rows2, int cols2) {
    if (cols1 != rows2) {
        fprintf(stderr, "Matrix dimensions do not allow multiplication.\n");
        exit(EXIT_FAILURE);
    }

    // Perform matrix multiplication
    for (int j = 0; j < cols2; j++) {
        for (int i = 0; i < rows1; i++) {
            for (int k = 0; k < cols2; k++) {
                result[i * cols2 + j] += mat1[i * cols1 + k] * mat2[k * cols2 + j];
            }
        }
    }
}
