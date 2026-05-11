#define _POSIX_C_SOURCE 200809L
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void die(const char *msg) { perror(msg); exit(EXIT_FAILURE); }

static void subscriber(int use_timeout) {
    int sig = SIGRTMIN;
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, sig);
    if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) die("sigprocmask");

    printf("Subscriber PID=%ld, waiting for SIGRTMIN (%d)\n", (long)getpid(), sig);
    for (;;) {
        siginfo_t si;
        int r;
        if (use_timeout) {
            struct timespec ts = { .tv_sec = 5, .tv_nsec = 0 };
            r = sigtimedwait(&set, &si, &ts);
        } else {
            r = sigwaitinfo(&set, &si);
        }

        if (r == -1) {
            if (errno == EAGAIN) { puts("timeout..."); continue; }
            die("sigwait");
        }
        printf("Received: %d from PID: %ld\n", si.si_value.sival_int, (long)si.si_pid);
        if (si.si_value.sival_int < 0) break;
    }
}

int main(int argc, char **argv) {
    if (argc < 2) return 1;
    if (strcmp(argv[1], "sub") == 0) subscriber(0);
    else if (strcmp(argv[1], "pub") == 0 && argc >= 4) {
        pid_t target = atoi(argv[2]);
        union sigval val;
        for (int i = 3; i < argc; i++) {
            val.sival_int = atoi(argv[i]);
            sigqueue(target, SIGRTMIN, val);
        }
    }
    return 0;
}
