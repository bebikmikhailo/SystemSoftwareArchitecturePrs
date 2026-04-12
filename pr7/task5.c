#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list(const char *path) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char full[512];

    while ((entry = readdir(dir))) {
        sprintf(full, "%s/%s", path, entry->d_name);

        struct stat st;
        stat(full, &st);

        printf("%s\n", full);

        if (S_ISDIR(st.st_mode) && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
            list(full);
        }
    }
    closedir(dir);
}

int main() {
    list(".");
    return 0;
}
