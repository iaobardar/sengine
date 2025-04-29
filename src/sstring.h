#ifndef SSTRING_H
#define SSTRING_H

#include <stddef.h>

// Type definitions
typedef struct
{
    size_t length;
    char* data;
} sstring;

typedef sstring sstringview;

// Function declarations
sstringview sv_cstr(char* cstr);
sstringview sv_ss(sstring* str, size_t i, size_t len);
char ssat(sstring* str, size_t i);
size_t ssfind(sstring* sample, sstring* input, size_t start_index);
void putss(sstring* str);

#endif // SSTRING_H