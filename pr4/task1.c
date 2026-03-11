#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

int main() {
    printf("sizeof(size_t) = %zu байтів\n", sizeof(size_t));

    size_t max_size = (size_t)-1;
    printf("Максимальне значення size_t: %zu\n", max_size);

    void *ptr = malloc(max_size);

    if (ptr == NULL) {
        printf("Не вдалося виділити пам'ять\n");
    } else {
        printf("Пам'ять виділилася\n");
        free(ptr);
    }

    return 0;
}
