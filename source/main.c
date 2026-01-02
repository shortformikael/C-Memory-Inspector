
#include "logger/logger.h"  // Include the header

int main(void) {
    log_info("Program started");
    
    // Your program logic here

    log_err("Program Error");
    
    log_info("Program finished");
    return 0;
}