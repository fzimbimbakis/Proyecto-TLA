#ifndef COMPILER_SUPERMALLOC_H
#define COMPILER_SUPERMALLOC_H
#include <stddef.h>

void initMemory();

void * superMalloc(int quantity,size_t size);

void superFree();

#endif //COMPILER_SUPERMALLOC_H
