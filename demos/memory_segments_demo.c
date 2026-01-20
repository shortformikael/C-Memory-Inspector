#include <stdio.h>
#include <stdlib.h>

// Global variables (data segment)
int global_initialized = 42;
static int static_initialized = 100;

// Uninitialized globals (BSS segment)
int global_uninitialized;
static int static_uninitialized;

void show_memory_segments() {
    // Local variable (stack)
    int stack_var = 1;
    
    // Heap allocation (heap)
    int *heap_var = malloc(sizeof(int));
    *heap_var = 2;
    
    // Static local variable (data segment)
    static int static_local = 3;
    
    // Code segment (function addresses)
    void *code_addr = show_memory_segments;
    
    printf("=== Memory Segments ===\n");
    printf("Code segment (text):  %p\n", code_addr);
    printf("Data segment (initialized): %p\n", &global_initialized);
    printf("Data segment (static):     %p\n", &static_local);
    printf("BSS segment (uninitialized): %p\n", &global_uninitialized);
    printf("Heap segment:              %p\n", heap_var);
    printf("Stack segment:             %p\n", &stack_var);
    
    printf("\n=== Address Patterns ===\n");
    printf("Low addresses (code/data): 0x0xxxxxxx\n");
    printf("Medium addresses (heap):   0x5xxxxxxx or 0x6xxxxxxx\n");
    printf("High addresses (stack):    0x7xxxxxxxxx\n");
    
    free(heap_var);
}

int main() {
    show_memory_segments();
    return 0;
}