#ifndef GROUND_H
#define GROUND_H

#include "glad/gl.h"
#include "vecmath.h"

typedef struct  {
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    GLuint element_count;
    GLuint program;
} ground_render_obj;

#endif GROUND_H