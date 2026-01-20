#include <stdio.h>

// Global variable (data segment)
int global_var = 1;

// Static global variable (data segment, internal linkage)
static int static_global = 2;

void show_memory_locations() {
    // Stack variable (stack)
    int stack_var = 3;
    
    // Static local variable (data segment)
    static int static_local = 4;
    
    printf("Memory locations:\n");
    printf("Global:       %p\n", &global_var);
    printf("Static global: %p\n", &static_global);
    printf("Static local:  %p\n", &static_local);
    printf("Stack var:     %p\n", &stack_var);
    
    printf("\nAddress ranges:\n");
    printf("Data segment (low): 0x40xxxxx\n");
    printf("Stack segment (high): 0x7xxxxxxxxx\n");
}

int main() {
    show_memory_locations();
    return 0;
}