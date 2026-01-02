#include "iterator.h"
#include "../logger/logger.h"
#include "../vector/vector.h"
#include <stdlib.h>

void iter_start() {
    log_info("Started Iterator");
    Vector *v = vec_init();

    vec_print(v);
    vec_free(v);

    log_info("Finished Iterator");
}
