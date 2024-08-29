#include <stdio.h>
#include <omp.h>
#include <time.h>

// Sequential matrix addition
void matrix_add_sequential(int n, int result[n][n]) {
    int a[n][n], b[n][n];
    
    // Initialize matrices
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            a[i][j] = i + j;
            b[i][j] = i - j;
        }

    // Sequential matrix addition
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = a[i][j] + b[i][j];
        }
    }
}

// Parallel matrix addition
double matrix_add_parallel(int n, int threads) {
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

    // Return time_taken for speedup calculation
    return time_taken;
}

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {12};

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 1; j++) {
            int n = sizes[i];
            int result[n][n];
            
            // Measure sequential execution time
            clock_t start_sequential = clock();
            matrix_add_sequential(n, result);
            clock_t end_sequential = clock();
            double time_sequential = (double)(end_sequential - start_sequential) / CLOCKS_PER_SEC;

            // Measure parallel execution time
            double time_parallel = matrix_add_parallel(n, threads[j]);

            // Calculate and print speedup
            double speedup = time_sequential / time_parallel;
            printf("Matrix size: %d, Threads: %d, Speedup: %f\n", n, threads[j], speedup);
        }
    }

    return 0;
}
