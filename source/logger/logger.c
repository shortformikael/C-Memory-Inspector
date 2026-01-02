#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

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

void log_err(const char* message) {
    char *now = get_now_str();
    fprintf(stderr, "[%s] [ERROR] %s\n", now, message);
    free(now);
}
