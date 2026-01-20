#include <stdio.h>

void demonstrate_static() {
    // Regular stack variable
    int stack_var = 1;
    stack_var++;
    printf("Stack var: %d (at %p)\n", stack_var, &stack_var);
    
    // Static variable
    static int static_var = 1;
    static_var++;
    printf("Static var: %d (at %p)\n", static_var, &static_var);
}

int main() {
    printf("=== Call 1 ===\n");
    demonstrate_static();
    
    printf("\n=== Call 2 ===\n");
    demonstrate_static();
    
    printf("\n=== Call 3 ===\n");
    demonstrate_static();
    
    return 0;
}