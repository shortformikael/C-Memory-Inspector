
#include "logger/logger.h"  // Include the header
#include "handler/handler.h"

int main(void) {
    log_info("Program started");

    handler_run();
    
    log_info("Program finished");
    return 0;
}