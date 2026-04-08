#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct block {
    size_t size;
    int free;
    struct block *next;
    struct block *prev;
} block_t;

#define BLOCK_SIZE sizeof(block_t)

static block_t *heap_head = NULL;
static block_t *heap_tail = NULL;

size_t align8(size_t size) {
    return ((size + 7) & ~7);
}

block_t *find_free_block(size_t size) {
    block_t *current = heap_head;
    while (current) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void split_block(block_t *block, size_t size) {
    if (block->size >= size + BLOCK_SIZE + 8) {
        block_t *new_block = (block_t *)((char *)(block + 1) + size);
        new_block->size = block->size - size - BLOCK_SIZE;
        new_block->free = 1;
        new_block->next = block->next;
        new_block->prev = block;

        if (new_block->next) {
            new_block->next->prev = new_block;
        } else {
            heap_tail = new_block;
        }

        block->size = size;
        block->next = new_block;
    }
}

block_t *request_space(size_t size) {
    void *request = sbrk(0);
    void *allocate = sbrk(size + BLOCK_SIZE);

    if (allocate == (void *) -1) {
        return NULL;
    }

    block_t *block = (block_t *)request;
    block->size = size;
    block->free = 0;
    block->next = NULL;
    block->prev = heap_tail;

    if (heap_tail) {
        heap_tail->next = block;
    }

    heap_tail = block;

    if (!heap_head) {
        heap_head = block;
    }

    return block;
}

void coalesce(block_t *block) {
    if (block->next && block->next->free) {
        block_t *next_block = block->next;
        block->size += BLOCK_SIZE + next_block->size;
        block->next = next_block->next;

        if (block->next) {
            block->next->prev = block;
        } else {
            heap_tail = block;
        }
    }

    if (block->prev && block->prev->free) {
        block_t *prev_block = block->prev;
        prev_block->size += BLOCK_SIZE + block->size;
        prev_block->next = block->next;

        if (block->next) {
            block->next->prev = prev_block;
        } else {
            heap_tail = prev_block;
        }
    }
}

void *my_malloc(size_t size) {
    if (size == 0) return NULL;

    size = align8(size);

    block_t *block = find_free_block(size);

    if (block) {
        block->free = 0;
        split_block(block, size);
        return (block + 1);
    }

    block = request_space(size);
    if (!block) return NULL;

    return (block + 1);
}

void my_free(void *ptr) {
    if (!ptr) return;

    block_t *block = (block_t *)ptr - 1;
    block->free = 1;
    coalesce(block);
}

void print_heap() {
    block_t *current = heap_head;
    printf("Стан блоків пам’яті:\n");
    while (current) {
        printf("Блок %p : розмір=%zu , вільний=%d , next=%p , prev=%p\n",
               (void *)current, current->size, current->free,
               (void *)current->next, (void *)current->prev);
        current = current->next;
    }
    printf("\n");
}

int main() {
    void *a = my_malloc(20);
    void *b = my_malloc(30);
    void *c = my_malloc(40);

    strcpy((char *)a, "Hello");
    strcpy((char *)b, "Allocator");
    strcpy((char *)c, "Memory");

    print_heap();

    my_free(b);
    printf("Після звільнення блоку B:\n");
    print_heap();

    my_free(a);
    printf("Після звільнення блоку A:\n");
    print_heap();

    void *d = my_malloc(25);
    strcpy((char *)d, "Повторно");
    printf("Після виділення блоку D:\n");
    print_heap();

    my_free(c);
    my_free(d);
    printf("Після звільнення всіх блоків:\n");
    print_heap();

    return 0;
}
