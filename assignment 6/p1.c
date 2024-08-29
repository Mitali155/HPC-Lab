#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 5 // Smaller Matrix size for testing

int main() {
    int i, j, k;
    double a[N][N], b[N][N], c[N][N];

    // Initialize matrices a and b
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            a[i][j] = rand() % 10; // Smaller values for easy verification
            b[i][j] = rand() % 10;
            c[i][j] = 0;
        }
    }

    // Print matrices a and b
    printf("Matrix A:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", b[i][j]);
        }
        printf("\n");
    }

    // Perform matrix-matrix multiplication using OpenMP
    #pragma omp parallel for private(i, j, k) shared(a, b, c)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            for (k = 0; k < N; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    // Print the result matrix
    printf("\nResultant Matrix C:\n");
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%f ", c[i][j]);
        }
        printf("\n");
    }
    return 0;
}
