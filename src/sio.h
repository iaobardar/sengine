#ifndef SIO_H
#define SIO_H

#include <stddef.h>

// Function declarations
size_t read_whole_file(const char* filename, void** data);

#endif // SIO_H