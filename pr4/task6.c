#include <stdio.h>
#include <stdlib.h>

int main() {

    int *ptr = NULL;

    ptr = realloc(NULL, 32);
    printf("realloc(NULL, 32) = %p\n", ptr);

    ptr = realloc(ptr, 0);
    printf("realloc(ptr, 0)\n");

    return 0;
}
