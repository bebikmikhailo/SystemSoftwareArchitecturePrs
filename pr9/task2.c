#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Спроба читання /etc/shadow через sudo:\n");
    system("sudo cat /etc/shadow");
    return 0;
}
