#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

   
    
    fcntl(pipefd[1], F_SETFL, O_NONBLOCK);

   
    char big_buffer[102400]; 
    memset(big_buffer, 'B', sizeof(big_buffer));

    int written = write(pipefd[1], big_buffer, sizeof(big_buffer));

    if (written >= 0) {
        printf("Запитано для запису: %zu байт\n", sizeof(big_buffer));
        printf("Фактично записано:   %d байт\n", written);
        
    } else {
        perror("Помилка запису");
    }

    return 0;
}
