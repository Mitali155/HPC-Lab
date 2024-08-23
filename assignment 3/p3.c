#include <stdio.h>
#include <omp.h>
void vector_scalar_addition(int *vector, int scalar, int *result, int size, int chunk_size, omp_sched_t schedule) {
    omp_set_schedule(schedule, chunk_size);
    
    #pragma omp parallel for schedule(runtime)
    for (int i = 0; i < size; i++) {
        result[i] = vector[i] + scalar;
    }
}
int main() {
    int size = 200;
    int vector[size], result[size];
    int scalar = 5;
    
    // Initialize vector
    for (int i = 0; i < size; i++) {
        vector[i] = i;
    }
    // Perform vector-scalar addition with static and dynamic schedules
    printf("STATIC schedule with chunk size 10:\n");
    vector_scalar_addition(vector, scalar, result, size, 10, omp_sched_static);

    printf("DYNAMIC schedule with chunk size 10:\n");
    vector_scalar_addition(vector, scalar, result, size, 10, omp_sched_dynamic);
    
    // Demonstrate nowait clause
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < size; i++) {
            result[i] = vector[i] + scalar;
        }
        printf("Completed without waiting.\n");
    }

    return 0;
}
