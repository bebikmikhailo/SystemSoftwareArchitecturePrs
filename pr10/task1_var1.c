#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int global_value = 10;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        global_value = 50;

        printf("Батьківський процес:\n");
        printf("PID = %d\n", getpid());
        printf("global_value = %d\n", global_value);
    } else {
        sleep(1);

        printf("Дочірній процес:\n");
        printf("PID = %d\n", getpid());
        printf("global_value = %d\n", global_value);
    }

    return 0;
}
