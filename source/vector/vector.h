#ifndef VECTOR_H
#define VECTOR_H
#include <stdint.h>

typedef struct Vector {
    int8_t x;
    int8_t y;
} Vector;

Vector* vec_init();
void vec_set(Vector *v, int x, int y);
void vec_increment(Vector *v);
void vec_print(Vector *v);
void vec_free(Vector *v);

#endif