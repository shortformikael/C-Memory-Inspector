#include "handler.h"
#include "../logger/logger.h"
#include "../vector/vector.h"
#include "../memoryinspector/memoryinspector.h"

void handler_run() {
    log_info("Started Handler");

    Vector *v = vec_init();
    minsp_log_vec("MALLOC", v);

    vec_free(v);
    minsp_log_vec("FREE", v);

    minsp_free();
    log_info("Finished Handler");
}
