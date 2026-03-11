#include <stdio.h>
#include <stdlib.h>

struct sbar {
    int a;
    double b;
};

int main() {

    struct sbar *ptr, *newptr;

    ptr = calloc(1000, sizeof(struct sbar));
    if (ptr == NULL) {
        printf("calloc повернув NULL\n");
        return 1;
    }

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));
    if (newptr == NULL) {
        printf("reallocarray повернув NULL\n");
        free(ptr);
        return 1;
    }

    ptr = newptr;

    printf("Вдалося перевиділити пам'ять\n");

    free(ptr);
    return 0;
}
