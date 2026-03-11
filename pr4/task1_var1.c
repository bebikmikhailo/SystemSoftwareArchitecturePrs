#define _GNU_SOURCE
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

#define MMAP_THRESHOLD 131072

typedef struct block {
    size_t size;
    int free;
    int mmaped;
    struct block *next;
    struct block *prev;
} block_t;

#define BLOCK_SIZE sizeof(block_t)

static block_t *heap_head = NULL;

block_t *find_free_block(size_t size) {
    block_t *curr = heap_head;
    while (curr) {
        if (curr->free && curr->size >= size && !curr->mmaped)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

void split_block(block_t *block, size_t size) {
    if (block->size <= size + BLOCK_SIZE)
        return;

    block_t *new_block = (block_t *)((char*)block + BLOCK_SIZE + size);
    new_block->size = block->size - size - BLOCK_SIZE;
    new_block->free = 1;
    new_block->mmaped = 0;
    new_block->next = block->next;
    new_block->prev = block;

    if (new_block->next)
        new_block->next->prev = new_block;

    block->size = size;
    block->next = new_block;
}

block_t *request_space(size_t size) {
    void *ptr = sbrk(size + BLOCK_SIZE);
    if (ptr == (void*)-1)
        return NULL;

    block_t *block = (block_t*)ptr;
    block->size = size;
    block->free = 0;
    block->mmaped = 0;
    block->next = NULL;
    block->prev = NULL;

    if (!heap_head)
        heap_head = block;
    else {
        block_t *curr = heap_head;
        while (curr->next)
            curr = curr->next;
        curr->next = block;
        block->prev = curr;
    }

    return block;
}

void *my_malloc(size_t size) {
    if (size == 0)
        return NULL;

    if (size >= MMAP_THRESHOLD) {
        size_t total = size + BLOCK_SIZE;
        block_t *block = mmap(NULL, total, PROT_READ | PROT_WRITE,
                              MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (block == MAP_FAILED)
            return NULL;

        block->size = size;
        block->free = 0;
        block->mmaped = 1;
        return (char*)block + BLOCK_SIZE;
    }

    block_t *block = find_free_block(size);

    if (block) {
        block->free = 0;
        split_block(block, size);
    } else {
        block = request_space(size);
        if (!block)
            return NULL;
    }

    return (char*)block + BLOCK_SIZE;
}

void merge_blocks(block_t *block) {
    if (block->next && block->next->free && !block->next->mmaped) {
        block->size += BLOCK_SIZE + block->next->size;
        block->next = block->next->next;
        if (block->next)
            block->next->prev = block;
    }
}

void my_free(void *ptr) {
    if (!ptr)
        return;

    block_t *block = (block_t*)((char*)ptr - BLOCK_SIZE);

    if (block->mmaped) {
        munmap(block, block->size + BLOCK_SIZE);
        return;
    }

    block->free = 1;

    if (block->next && block->next->free)
        merge_blocks(block);

    if (block->prev && block->prev->free)
        merge_blocks(block->prev);
}

void print_heap() {
    block_t *curr = heap_head;
    while (curr) {
        printf("Block size: %zu free: %d\n", curr->size, curr->free);
        curr = curr->next;
    }
}

int main() {
    void *a = my_malloc(100);
    void *b = my_malloc(200);
    void *c = my_malloc(300);

    my_free(b);

    void *d = my_malloc(150);

    print_heap();

    my_free(a);
    my_free(c);
    my_free(d);

    return 0;
}
