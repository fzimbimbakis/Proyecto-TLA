#include "supermalloc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint-gcc.h>

#define BUFFER_SIZE 1000
void ** memoryAllocs;
int nAllocs;
void initMemory(){
    nAllocs = 0;
    memoryAllocs = NULL;
}
void * superMalloc(int quantity, size_t size){
    void * new = calloc(quantity,size);
    if(new == NULL){
        printf("Error on malloc!\n");
        abort();
    }
    if(nAllocs % BUFFER_SIZE == 0){
        memoryAllocs = realloc(memoryAllocs, (nAllocs + BUFFER_SIZE) * sizeof(void *));
    }
    if(memoryAllocs == NULL){
        superFree();
        abort();
    }


    memoryAllocs[nAllocs++] = new;
    return new;
}

void superFree(){
    for (int i = 0; i < nAllocs; ++i) {
        free(memoryAllocs[i]);
    }
}
