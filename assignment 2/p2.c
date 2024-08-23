#include <stdio.h>
#include <omp.h>

int main() {
    long num_steps = 1000000000; // Number of intervals
    double step, pi = 0.0;
    step = 1.0/(double) num_steps;

    // Parallel calculation of Pi using reduction
    #pragma omp parallel
    {
        double sum = 0.0;
        int i;
        #pragma omp for
        for (i = 0; i < num_steps; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
        #pragma omp critical
        pi += sum;
    }

    pi *= step;
    printf("Calculated Pi value: %.15f\n", pi);

    return 0;
}
