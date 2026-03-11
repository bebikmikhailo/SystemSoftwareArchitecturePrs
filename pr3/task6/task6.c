#include <stdio.h>


void stack_overflow(int level) {
    int ints[1024 * 100] = {1};

    printf("Рівень рекурсії: %d, виділено %d кб\n", level, level * 100 * 4);

    stack_overflow(level + 1);

}

int main(void) {

    stack_overflow(1);

    return 0;
}
