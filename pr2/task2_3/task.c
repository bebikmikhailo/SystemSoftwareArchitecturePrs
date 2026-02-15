#include <stdio.h>
#include <stdlib.h>

int global_data = 100;

int global_bss;

void test_function() {
	int array1[1000] = {2};
	int array2[1000] = {3};
} 

int main() {
    int stack_var;

    int *heap_var = (int *)malloc(sizeof(int));
    test_function();

    printf("Сегмент TEXT: %p\n", (void*)&test_function);
    printf("Сегмент DATA: %p\n", (void*)&global_data);
    printf("Сегмент BSS: %p\n", (void*)&global_bss);
    printf("Сегмент HEAP: %p\n", (void*)heap_var);
    printf("STACK: %p\n", (void*)&stack_var);

    free(heap_var);
    return 0;
}
