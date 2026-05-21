#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_ARGS 64

int main() {
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Мініоболонка запущена. Для виходу введіть 'exit'.\n");

    while (1) {
        printf("minishell> ");
        
        read = getline(&line, &len, stdin);

        if (read == -1) {
            printf("\n");
            break;
        }

        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
        }

        if (strlen(line) == 0) {
            continue;
        }

        char *args[MAX_ARGS];
        char *token = strtok(line, " ");
        int i = 0;
        
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("Помилка: не вдалося виконати fork()");
        } else if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("Помилка запуску команди");
                exit(EXIT_FAILURE);
            }
        } else {
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("Помилка: waitpid()");
            } else {
                if (WIFEXITED(status)) {
                    printf("[Процес завершено з кодом: %d]\n", WEXITSTATUS(status));
                } else if (WIFSIGNALED(status)) {
                    printf("[Процес вбито сигналом: %d]\n", WTERMSIG(status));
                }
            }
        }
    }

    free(line);
    return 0;
}
