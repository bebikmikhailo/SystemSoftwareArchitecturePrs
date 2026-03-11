#include <stdio.h>
#include <stdlib.h>

int main() {

    char *ptr = malloc(16);

    char *tmp = realloc(ptr, (size_t)1e18);

    if (tmp == NULL) {
        printf("Невдалося перевиділити пам'ять, стара пам'ять ще є дійсною\n");
        free(ptr);
    } else {
        ptr = tmp;
        free(ptr);
    }

    return 0;
}
