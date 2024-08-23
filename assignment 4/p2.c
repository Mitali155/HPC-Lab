#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
int count = 0;
#pragma omp declare reduction(sum: int: omp_out += omp_in)

void produce() {
    int item = rand() % 100;
    #pragma omp critical
    {
        if (count < BUFFER_SIZE) {
            buffer[count] = item;
            count++;
            printf("Produced: %d\n", item);
        }
    }
}
void consume() {
    #pragma omp critical
    {
        if (count > 0) {
            int item = buffer[--count];
            printf("Consumed: %d\n", item);
        }
    }
}
int main() {
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for (int i = 0; i < 20; i++) {
                produce();
            }
        }
        #pragma omp section
        {
            for (int i = 0; i < 20; i++) {
                consume();
            }
        }
    }
    return 0;
}
