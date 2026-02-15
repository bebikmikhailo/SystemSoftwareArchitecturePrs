#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t low = 0;
    size_t high = 1024UL * 1024 * 1024 * 4; // 4 ГБ (можна змінити)
    size_t mid;
    void *ptr;

    while (low <= high) {
        mid = (low + high) / 2;
        ptr = malloc(mid);

        if (ptr != NULL) {
            free(ptr);
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("Максимальний можливий розмір сегмента кучі: %zu мегабайтів\n", high / 1048576);
    return 0;
}
