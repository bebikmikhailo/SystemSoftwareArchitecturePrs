#include <stdio.h>
#include <dirent.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return strcmp(*(char**)a, *(char**)b);
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    char *dirs[100];
    int count = 0;

    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_DIR &&
            strcmp(entry->d_name, ".") &&
            strcmp(entry->d_name, "..")) {
            dirs[count++] = entry->d_name;
        }
    }

    qsort(dirs, count, sizeof(char*), cmp);

    for (int i = 0; i < count; i++) {
        printf("%s\n", dirs[i]);
    }

    closedir(dir);
}
