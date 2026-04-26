#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("HOME:\n");
    system("ls -l ~");

    printf("\n/usr/bin:\n");
    system("ls -l /usr/bin");

    printf("\n/etc:\n");
    system("ls -l /etc");

    printf("\nСпроба читання /etc/shadow:\n");
    system("cat /etc/shadow");

    printf("\nСпроба запису в /usr/bin:\n");
    system("touch /usr/bin/testfile");

    return 0;
}
