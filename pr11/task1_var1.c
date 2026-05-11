#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <execinfo.h>
#include <string.h>

char *program_name;

void segv_handler(int sig, siginfo_t *info, void *context) {
    FILE *log = fopen("crash.log", "a");

    if (log) {
        fprintf(log, "\n    SIGSEGV відловлена   \n");
        fprintf(log, "PID: %d\n", getpid());
        fprintf(log, "Сигнал: %d\n", sig);
        fprintf(log, "Адреса помилки: %p\n", info->si_addr);

        void *buffer[20];
        int size = backtrace(buffer, 20);

        fprintf(log, "Трасування стека:\n");
        backtrace_symbols_fd(buffer, size, fileno(log));

        fprintf(log, "\nПерезапуск програми...\n");
        fclose(log);
    }

    char *args[] = { program_name, NULL };

    execvp(program_name, args);

    perror("execvp");
    exit(1);
}

void install_handler() {
    struct sigaction sa;

    memset(&sa, 0, sizeof(sa));

    sa.sa_sigaction = segv_handler;
    sa.sa_flags = SA_SIGINFO;

    sigaction(SIGSEGV, &sa, NULL);
}

void crash() {
    int *p = NULL;
    *p = 100;
}

int main(int argc, char *argv[]) {
    program_name = argv[0];

    install_handler();

    printf("PID: %d\n", getpid());
    printf("Програма видасть зараз видасть помилку...\n");

    sleep(1);

    crash();

    return 0;
}
