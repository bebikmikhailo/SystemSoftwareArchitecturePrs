#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;

    while ((entry = readdir(dir))) {
        printf("Видалити %s? (y/n): ", entry->d_name);
        char c = getchar();
        getchar();

        if (c == 'y') {
            remove(entry->d_name);
        }
    }

    closedir(dir);
}
