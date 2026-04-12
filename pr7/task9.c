#include <stdio.h>
#include <time.h>

int main() {
    clock_t start = clock();

    for (int i = 0; i < 100000000; i++);

    clock_t end = clock();

    double time_ms = (double)(end - start) * 1000 / CLOCKS_PER_SEC;
    printf("Час: %.2f ms\n", time_ms);
}
