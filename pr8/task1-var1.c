#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <signal.h>

int main() {
    mkfifo("myfifo", 0666);

    signal(SIGPIPE, SIG_IGN);

    int fd = open("myfifo", O_WRONLY | O_NONBLOCK);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    int result = write(fd, "Hello", 5);

    if (result == -1) {
        perror("write");
    } else {
        printf("Записано %d байт\n", result);
    }

    close(fd);
    return 0;
}
