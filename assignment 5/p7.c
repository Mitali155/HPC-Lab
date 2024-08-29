#include <stdio.h>
#include <omp.h>
int main() {
    int total_sum = 0;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    // Unsynchronized version
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    printf("Unsynchronized Total Sum = %d\n", total_sum);
    // Synchronized version using critical
    total_sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp critical
        total_sum += arr[i];
    }
    printf("Synchronized (Critical) Total Sum = %d\n", total_sum);
    // Synchronized version using atomic
    total_sum = 0;
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        #pragma omp atomic
        total_sum += arr[i];
    }
    printf("Synchronized (Atomic) Total Sum = %d\n", total_sum);
    return 0;
}