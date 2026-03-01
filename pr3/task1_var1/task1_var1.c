#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void* thread_func(void* arg) {
    pause(); // потік просто висить у пам'яті
    return NULL;
}

int main() {
    pthread_t t;
    int count = 0;
    while(1) {
        int res = pthread_create(&t, NULL, thread_func, NULL);
        if (res != 0) {
            printf("\nСтворено потоків: %d. Помилка: %s\n", count, strerror(res));
            break;
        }
        count++;
        if (count % 10 == 0) printf("Потоків створено: %d\n", count);
    }
    return 0;
}
