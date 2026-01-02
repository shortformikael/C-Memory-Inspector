#include "vector.h"
#include "../logger/logger.h"
#include <stdio.h>
#include <stdlib.h>

Vector* vec_init() {
    Vector *r_vec = malloc(sizeof(*r_vec));

    r_vec->x = 0;
    r_vec->y = 0;

    return r_vec;
}

void vec_set(Vector *v, int x, int y) {
    v->x = x;
    v->y = y;
}

void vec_increment(Vector *v) {
    v->x++;
    v->y++;
}

void vec_print(Vector *v) {
    char message_buffer[256];
    sprintf(message_buffer, "Vector coordinates: %d,%d", v->x, v->y);
    log_info(message_buffer);
}

void vec_free(Vector *v) {
    free(v);
}