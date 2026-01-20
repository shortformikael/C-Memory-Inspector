#include <stdio.h>
#include <stdlib.h>

// Code segment: This function will be compiled to machine code
void demonstrate_segments() {
    // Stack segment: Local variables, parameters, return address
    int local_var = 1;
    char local_array[100];
    
    // Heap segment: Dynamic allocation
    int *heap_ptr = malloc(sizeof(int) * 100);
    *heap_ptr = 42;
    
    printf("Stack variable:   %p\n", &local_var);
    printf("Heap allocation:  %p\n", heap_ptr);
    
    free(heap_ptr);
}

// Data segment: Initialized global variables
int initialized_global = 100;
static char message[] = "This is in data segment";

// BSS segment: Uninitialized global variables  
int uninitialized_global;
static long uninitialized_static;

int main() {
    printf("=== Memory Segments Demonstration ===\n");
    
    // Code segment address (function pointer)
    printf("Code (main):       %p\n", main);
    printf("Code (demonstrate): %p\n", demonstrate_segments);
    
    // Data segment addresses
    printf("Data (global):     %p\n", &initialized_global);
    printf("Data (static):     %p\n", &message);
    
    // BSS segment addresses  
    printf("BSS (uninit):      %p\n", &uninitialized_global);
    
    demonstrate_segments();
    
    printf("\n=== Memory Layout Visualization ===\n");
    printf("High addresses: Stack  (grows down)\n");
    printf("                ^\n");
    printf("                |\n");
    printf("Medium addresses: Heap   (grows up)\n");
    printf("                |\n");
    printf("                v\n");
    printf("Low addresses:  Data/BSS/Code (fixed)\n");
    
    return 0;
}