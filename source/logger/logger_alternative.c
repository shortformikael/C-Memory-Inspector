#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Alternative stack-based approach - showing what you were missing
char* get_now_str_stack() { // returns pointer to stack memory
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    static char stack_buffer[64]; // static to survive function return
    
    strftime(stack_buffer, 64, "%H:%M:%S", local);
    
    return stack_buffer; // safe because it's static
}

// Your original heap-based approach
char* get_now_str() { // returns heap memory pointer
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char *r_var = malloc(64 * sizeof(char));

    strftime(r_var, 64, "%H:%M:%S", local);
    
    return r_var;
}

void log_info(const char* message) {
    char *now = get_now_str();
    printf("[%s] [INFO] %s\n", now, message);
    free(now);
}

void log_info_stack(const char* message) {
    char *now = get_now_str_stack();
    printf("[%s] [INFO] %s\n", now, message);
    // No free needed - static allocation
}

void log_err(const char* message) {
    char *now = get_now_str();
    fprintf(stderr, "[%s] [ERROR] %s\n", now, message);
    free(now);
}