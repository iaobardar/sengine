#include <stdio.h>
#include <stdlib.h>
#include "sio.h"

size_t read_whole_file(const char* filename, void** data)
{
    const size_t read_chunk_size = 512;

    FILE* in_file = fopen(filename, "rb");
    if (!in_file) return 0;

    size_t used = 0;
    size_t allocated = 0;
    *data = NULL;

    do
    {
        allocated += read_chunk_size;
        *data = realloc(*data, allocated);
        
        if (!*data) {puts("Out of memory for file read."); exit(1);}

        used += fread(data + used, 1, allocated - used, in_file);
        //printf("read loop %zi %zi\n", allocated, used);
    }
    while (used == allocated);

    // shrink back to fit only the used portion.
    allocated = used;
    *data = realloc(*data, allocated);

    fclose(in_file);
    return allocated;
}