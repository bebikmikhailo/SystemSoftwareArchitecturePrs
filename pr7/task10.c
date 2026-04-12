#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));

    double n = 10.0;

    for (int i = 0; i < 5; i++) {
        printf("0-1: %f\n", (double)rand()/RAND_MAX);
        printf("0-n: %f\n", ((double)rand()/RAND_MAX) * n);
    }
}
