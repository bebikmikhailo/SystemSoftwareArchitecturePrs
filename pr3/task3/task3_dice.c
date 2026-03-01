#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void handle_sigxfsz(int sig) {
    printf("\n Сигнал SIGXFSZ отримано \n");
    printf("Перевищено обмеження максимального розміру файлу (ulimit -f)!\n");
    printf("Програма завершує роботу коректно.\n");
    exit(0);
}

int main() {
    if (signal(SIGXFSZ, handle_sigxfsz) == SIG_ERR) {
        perror("Не вдалося встановити обробник SIGXFSZ");
        return 1;
    }

    FILE *fp = fopen("dice_rolls.txt", "w");
    if (fp == NULL) {
        perror("Не вдалося відкрити файл dice_rolls.txt для запису");
        return 1;
    }

    srand(time(NULL));

    printf("Імітація кидків шестигранного кубика запущена.\n");
    printf("Результати записуються у файл 'dice_rolls.txt'\n");

    long long roll_count = 0;

    while (1) {
        int roll = (rand() % 6) + 1;
        fprintf(fp, "%d\n", roll);
        roll_count++;

        if (roll_count % 5000 == 0) {
            printf("Виконано кидків: %lld\n", roll_count);
            fflush(stdout);
        }
    }

    fclose(fp);
    return 0;
}