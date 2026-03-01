#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    FILE *dest = fopen(argv[2], "w");
    if (!dest) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(src);
        return 1;
    }

    char ch;
    while ((ch = fgetc(src)) != EOF) {
        if (fputc(ch, dest) == EOF) {
            printf("\n[ПОМИЛКА] Перевищено обмеження на розмір файлу!\n");
            break;
        }
    }

    fclose(src);
    fclose(dest);
    return 0;
}