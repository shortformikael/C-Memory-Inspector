#ifndef MEMORYINSPECTOR_H
#define MEMORYINSPECTOR_H
#include <stddef.h>
#include <stdlib.h>


#define malloc(size) minsp_malloc(size, __FILE__, __LINE__)
#define free(ptr) minsp_free(ptr, __FILE__, __LINE__)

void minsp_free_all();

void* minsp_malloc(size_t size, const char *file, int line);
void minsp_free(void *ptr, const char *file, int line);

#endif