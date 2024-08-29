#include <stdio.h>
#include <omp.h>

int main() {
    int n = 1000000;  // Large array size
    int *arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Sequential version
    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    printf("Sequential Total Sum = %d\n", total_sum);

    // Parallel version using reduction
    total_sum = 0;
    #pragma omp parallel for reduction(+:total_sum)
    for (int i = 0; i < n; i++) {
        total_sum += arr[i];
    }
    printf("Parallel Total Sum using reduction = %d\n", total_sum);

    free(arr);

    return 0;
}