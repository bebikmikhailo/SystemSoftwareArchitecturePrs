#include <stdio.h>

int main() {
    int neighbour_value = 100;      // сусідня змінна в стеку
    int arr[3] = {1, 2, 3};

    int sum = 0;

    for (int i = 0; i <= 3; i++) {   // помилка: має бути i < 3
        sum += arr[i];               // arr[3] читає чужу пам'ять
    }

    printf("Сусідне значення масиву: %d\n", neighbour_value);
    printf("Сума масиву = %d\n", sum);

    return 0;
}
