#ifndef SSHADER_H
#define SSHADER_H

#include <stddef.h>
#include <glad/gl.h>
// #include <GL/gl.h>
#include "sstring.h"
#include "sio.h"

// Type definitions
typedef struct {
    size_t count;
    sstringview shaders[10];
    sstring src;
} shaderlistfile;

// Function declarations
shaderlistfile load_shader_file(char* filename);
GLuint init_shader(GLuint type, sstring* src);
GLuint init_shader_program(sstring* vert_src, sstring* frag_src);

#endif // SSHADER_H