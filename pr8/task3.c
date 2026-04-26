#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

void fill_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = i;
}

void fill_reverse(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = n - i;
}

void fill_random(int *arr, int n) {
    for (int i = 0; i < n; i++) arr[i] = rand();
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++)
        if (arr[i] < arr[i-1]) return 0;
    return 1;
}

void test_case(void (*fill)(int*, int), int n, const char *name) {
    int *arr = malloc(n * sizeof(int));
    fill(arr, n);

    clock_t start = clock();
    qsort(arr, n, sizeof(int), cmp);
    clock_t end = clock();

    printf("%s: %.2f ms, sorted=%d\n",
           name,
           (double)(end - start) * 1000 / CLOCKS_PER_SEC,
           is_sorted(arr, n));

    free(arr);
}

int main() {
    srand(time(NULL));

    int n = 100000;

    test_case(fill_sorted, n, "Sorted");
    test_case(fill_reverse, n, "Reverse");
    test_case(fill_random, n, "Random");

    return 0;
}
