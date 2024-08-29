#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int n = 1000;
    int *arr;
    int sum = 0;
    // Allocate memory for the array
    arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    // Initialize the array with some values
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    // Calculate the sum of array elements in parallel
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    printf("Sum of array elements = %d\n", sum);
    // Free the allocated memory
    free(arr);
    return 0;
}