#include "vector.h"
#include "../logger/logger.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Vector* vec_init() {
    Vector *r_vec = malloc(sizeof(*r_vec));
    r_vec->x = 0;
    r_vec->y = 0;

    return r_vec;
}

void vec_set(Vector *v, int x, int y) {
    if (INT8_MIN < x && x < INT8_MAX) {
        v->x = x;
    } else {
        if (INT8_MIN >= x) {
            v->x = INT8_MIN;
        } else {
            v->x = INT8_MAX;
        }
    }

    if (INT8_MIN < y && y < INT8_MAX) {
        v->y = y;
    } else {
        if (INT8_MIN >= y) {
            v->y = INT8_MIN;
        } else {
            v->y = INT8_MAX;
        }
    }
}

void vec_increment(Vector *v) {
    vec_set(v, v->x+1, v->y+1);    
}

void vec_print(Vector *v) {
    char message_buffer[256];
    sprintf(message_buffer, "Vector coordinates: %d,%d", v->x, v->y);
    log_info(message_buffer);
}

void vec_free(Vector *v) {
    free(v);
}