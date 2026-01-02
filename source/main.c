
#include "logger/logger.h"  // Include the header
#include "iterator/iterator.h"

int main(void) {
    log_info("Program started");

    iter_start();
    
    log_info("Program finished");
    return 0;
}