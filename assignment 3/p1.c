#include <stdio.h>
#include <omp.h>
#include <limits.h>

int main() {
    int n = 1000;
    int a[n], b[n];
    int min_product = INT_MAX;

    // Initialize vectors with some values
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        b[i] = n - i;
    }

    // Calculate minimum scalar product using reduction
    #pragma omp parallel for reduction(min:min_product)
    for (int i = 0; i < n; i++) {
        int product = a[i] * b[i];
        if (product < min_product) {
            min_product = product;
        }
    }

    printf("Minimum scalar product: %d\n", min_product);

    return 0;
}
