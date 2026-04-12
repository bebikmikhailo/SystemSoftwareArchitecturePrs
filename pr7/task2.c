#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main() {
    DIR *dir = opendir(".");
    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir))) {
        stat(entry->d_name, &st);
        print_permissions(st.st_mode);
        printf(" %ld %s\n", st.st_size, entry->d_name);
    }

    closedir(dir);
    return 0;
}
