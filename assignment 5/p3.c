#include <stdio.h>
#include <omp.h>

int main() {
    int Aryabhatta = 10;

    #pragma omp parallel private(Aryabhatta)
    {
        int thread_id = omp_get_thread_num();
        int result = thread_id * Aryabhatta;
        printf("Thread %d: Result = %d\n", thread_id, result);
    }

    return 0;
}