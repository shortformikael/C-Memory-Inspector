#include "handler.h"
#include "../logger/logger.h"
#include "../memoryinspector/memoryinspector.h"
#include "../vector/vector.h"

void handler_run() {
    log_info("Started Handler");

    Vector *v = vec_init();
    
    // minsp_free_all();
    vec_free(v);
    log_info("Finished Handler");
}
