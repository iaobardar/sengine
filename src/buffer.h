#include <stdlib.h>
//#include <stdio.h>

static inline int grow_buffer(void** buffer, size_t* allocated, size_t needed)
{
    if (needed <= *allocated) return 1;

    size_t to_allocate = (*allocated >= 2) ? *allocated : 2;
    while(needed > to_allocate)
        to_allocate += to_allocate >> 1;

    if (to_allocate < *allocated) return 0; // integer overflow check

    //printf("\tReallocating buffer from %zu to %zu bytes\n", *allocated, to_allocate);

    void* new_mem = realloc(*buffer, to_allocate);
    if (new_mem == NULL)
        return 0;
     
    *buffer = new_mem;
    *allocated = to_allocate;
    return 1;
}

static inline void free_buffer(void** buffer, size_t* allocated)
{
    free(*buffer);
    *buffer = NULL;
    *allocated = 0;
}