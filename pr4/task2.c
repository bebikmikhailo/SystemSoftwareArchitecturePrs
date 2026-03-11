#include <stdio.h>
#include <stdlib.h>

int main() {

    int xa = 100000;
    int xb = 100000;

    int num = xa * xb;

    printf("xa = %d\n", xa);
    printf("xb = %d\n", xb);
    printf("num (xa * xb) = %d\n", num);

    void *ptr = malloc(num);

    if (ptr == NULL) {
        printf("Пам'ять виділилася\n");
    } else {
        printf("Не вдалось виділити пам'ять\n");
        free(ptr);
    }

    return 0;
}
