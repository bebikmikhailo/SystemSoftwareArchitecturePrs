#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    printf("Розмір time_t: %zu біт (%zu байт)\n", sizeof(time_t) * 8, sizeof(time_t));

    time_t max_time_4 = (time_t) INT_MAX;
    time_t max_time_8 = (time_t) LLONG_MAX;


    printf("Максимальне значення (4 байти): %lld\n", (long long)max_time_4);
    printf("Дата: %s\n", ctime(&max_time_4));

    printf("Максимальне значення (8 байтів): %lld\n", (long long)max_time_8);
    printf("Дата: %s\n", ctime(&max_time_8));

    max_time_8 += 1;

    printf("Значення після +1 секунди: %lld\n", (long long)max_time_8);
    printf("Дата після переповнення: %s\n", ctime(&max_time_8));

    return 0;
}
