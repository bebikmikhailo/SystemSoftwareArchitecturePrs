#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *fp = popen("getent passwd", "r");
    if (!fp) {
        perror("popen");
        return 1;
    }

    char line[512];
    char username[100];
    int uid;

    printf("Користувачі з UID > 1000:\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^:]:x:%d", username, &uid);

        if (uid > 1000) {
            printf("%s (UID=%d)\n", username, uid);
        }
    }

    pclose(fp);
    return 0;
}
