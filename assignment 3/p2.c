#include <stdio.h>
#include <omp.h>
#include <time.h>
void matrix_add(int n, int threads) {
    int a[n][n], b[n][n], result[n][n];
    omp_set_num_threads(threads);
    
    // Initialize matrices
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }
    clock_t start = clock();
    // Parallel matrix addition
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Matrix size: %d, Threads: %d, Time taken: %f seconds\n", n, threads, time_taken);
}
int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {2, 4, 8};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++) {
            matrix_add(sizes[i], threads[j]);
        }
    }

    return 0;
}
