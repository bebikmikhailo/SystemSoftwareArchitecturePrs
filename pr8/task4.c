#include <stdio.h>
#include <unistd.h>

int main() {
    int pid = fork();

    if (pid == 0) {
        printf("Дочірній процес: pid = %d\n", pid);
    } else {
        printf("Батьківський процес: pid = %d\n", pid);
    }

    return 0;
}
