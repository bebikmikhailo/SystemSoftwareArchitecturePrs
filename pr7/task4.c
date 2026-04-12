#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *f = fopen(argv[1], "r");
    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
        count++;

        if (count == 20) {
            getchar();
            count = 0;
        }
    }

    fclose(f);
    return 0;
}
