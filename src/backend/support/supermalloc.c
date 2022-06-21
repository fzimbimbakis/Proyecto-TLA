#include "supermalloc.h"
#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 10
void ** memoryAllocs;
int nAllocs;
void initMemory(){
    nAllocs = 0;
    memoryAllocs = NULL;
}
void * superMalloc(size_t size){
    void * new = malloc(size);
    if(new == NULL){
        printf("Error on malloc!\n");
        abort();
    }
    if(nAllocs % BUFFER_SIZE == 0){
        memoryAllocs = realloc(memoryAllocs, (nAllocs + BUFFER_SIZE) * sizeof(void *));
    }
    memoryAllocs[nAllocs++] = new;
}

void superFree(){
    for (int i = 0; i < nAllocs; ++i) {
        free(memoryAllocs[i]);
    }
}
