#include <stdio.h>
#include <stdlib.h>

int main() {
    system("echo 'data' > shared.txt");
    system("chmod 666 shared.txt");

    printf("Інший користувач може змінити файл через права доступу:\n");
    system("echo 'modified' >> shared.txt");

    printf("Вміст файлу:\n");
    system("cat shared.txt");

    return 0;
}
