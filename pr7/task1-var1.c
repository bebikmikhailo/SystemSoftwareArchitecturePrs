#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void tree(const char *path, int level) {
    DIR *dir = opendir(path);
    struct dirent *entry;
    char full[512];

    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        for (int i = 0; i < level; i++) printf("  ");

        printf("%s\n", entry->d_name);

        sprintf(full, "%s/%s", path, entry->d_name);

        struct stat st;
        lstat(full, &st);

        if (S_ISDIR(st.st_mode)) {
            tree(full, level + 1);
        }
    }

    closedir(dir);
}

int main() {
    tree("/", 0);
    return 0;
}
