#include <stdio.h>
#include <stdlib.h>

int main() {
    system("echo 'test data' > user_file.txt");

    printf("Копіювання від root...\n");
    system("sudo cp user_file.txt /root/root_copy.txt");

    printf("Повертаємо файл у домашню директорію...\n");
    system("sudo cp /root/root_copy.txt ./copy.txt");

    printf("Спроба змінити файл:\n");
    system("echo 'new data' >> copy.txt");

    printf("Спроба видалити файл:\n");
    system("rm copy.txt");

    return 0;
}
