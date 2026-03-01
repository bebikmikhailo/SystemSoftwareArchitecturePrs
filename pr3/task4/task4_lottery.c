#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t cpu_limit_exceeded = 0;

void handle_sigxcpu(int sig) {
    printf("\nCPU time limit exceeded! Finishing program safely...\n");
    cpu_limit_exceeded = 1;
}

void generate_unique(int arr[], int count, int max) {
    int used[100] = {0};
    int i = 0;

    while (i < count) {
        int num = rand() % max + 1;
        if (!used[num]) {
            used[num] = 1;
            arr[i++] = num;
        }
    }
}

int main() {
    signal(SIGXCPU, handle_sigxcpu);
    srand(time(NULL));

    int lotto1[7];
    int lotto2[6];

    while (!cpu_limit_exceeded) {

        generate_unique(lotto1, 7, 49);
        generate_unique(lotto2, 6, 36);

        printf("\n7 from 49: ");
        for (int i = 0; i < 7; i++)
            printf("%d ", lotto1[i]);

        printf("\n6 from 36: ");
        for (int i = 0; i < 6; i++)
            printf("%d ", lotto2[i]);

        printf("\n------------------------\n");

        // Штучне навантаження CPU
        for (volatile long i = 0; i < 50000000; i++);
    }

    printf("Program terminated correctly.\n");
    return 0;
}