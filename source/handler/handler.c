#include "handler.h"
#include "../logger/logger.h"
#include "../vector/vector.h"

void handler_run() {
    log_info("Started Handler");

    Vector *v = vec_init();
    vec_print(v);

    // vec_increment(v);
    // vec_print(v);

    // vec_set(v, 120, -32);
    // vec_print(v);

    vec_free(v);
    log_info("Finished Handler");
}
