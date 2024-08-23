#include <stdio.h>
#include <omp.h>
// Function to perform vector-scalar addition using OpenMP
void vector_scalar_addition(int *vector, int scalar, int *result, int size) {
    #pragma omp parallel for
    for (int i = 0; i < size; i++) {
        result[i] = vector[i] + scalar;
    }
}
int main() {
    int size = 100000;  // Size of the vector
    int vector[size], result[size];
    int scalar = 5;
    // Initialize the vector with values
    for (int i = 0; i < size; i++) {
        vector[i] = i;
    }
    // Perform vector-scalar addition
    vector_scalar_addition(vector, scalar, result, size);
    // Print the first 10 elements of the result for verification
    printf("Result:\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    return 0;
}