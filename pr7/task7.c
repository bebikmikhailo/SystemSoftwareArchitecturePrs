#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir))) {
        if (strstr(entry->d_name, ".c")) {
            printf("Файл: %s. Дати права на читання? (y/n): ", entry->d_name);
            char c = getchar();
            getchar();

            if (c == 'y') {
                struct stat st;
                stat(entry->d_name, &st);
                chmod(entry->d_name, st.st_mode | S_IROTH);
            }
        }
    }

    closedir(dir);
}
