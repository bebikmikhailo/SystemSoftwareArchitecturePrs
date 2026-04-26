#include <stdio.h>
#include <stdlib.h>

int main() {
    system("echo 'temp file' > temp.txt");

    printf("Зміна прав через root...\n");
    system("sudo chown root:root temp.txt");
    system("sudo chmod 600 temp.txt");

    printf("Спроба читання:\n");
    system("cat temp.txt");

    printf("Спроба запису:\n");
    system("echo 'data' >> temp.txt");

    return 0;
}
