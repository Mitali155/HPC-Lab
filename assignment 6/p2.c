#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 500 // Matrix size (N x N)
#define M 500 // Vector size (M x 1)
int main() {
    int i, j;
    double a[N][M], x[M], y[N];
    // Initialize matrix a and vector x
    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            a[i][j] = rand() % 100;
        }
    }
    for (j = 0; j < M; j++) {
        x[j] = rand() % 100;
    }
    // Perform matrix-vector multiplication using OpenMP
    #pragma omp parallel for private(i, j) shared(a, x, y)
    for (i = 0; i < N; i++) {
        y[i] = 0;
        for (j = 0; j < M; j++) {
            y[i] += a[i][j] * x[j];
        }
    }
    // Print a portion of the result vector
    printf("Resultant vector y[0] = %f\n", y[0]);

    return 0;
}
