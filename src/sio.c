#include <stdio.h>
#include <stdlib.h>
#include "sio.h"

static const size_t read_chunk_size = 512;

size_t read_whole_file(const char* filename, void** data)
{
    //*data = (void*)-1;

    FILE* in_file = fopen(filename, "rb");
    if (!in_file) return 0;

    size_t used = 0;
    size_t allocation = 0;

    *data = 0;

    while (used == allocation)
    {
        allocation += read_chunk_size;
        *data = realloc(*data, allocation);
        
        if (!*data) {puts("Out of memory for file read."); exit(1);}

        used += fread((char *)(*data) + used, 1, allocation - used, in_file);
        printf("read loop %zi %zi\n", allocation, used);
    }

    

    fclose(in_file);
    *data = realloc(*data, used); // shrink back to fit only the used portion.

    puts("lol");

    return used;
}