#include "glad/gl.h"
#include "vecmath.h"

typedef struct cube_render_obj {
    mat4 model_matrix;
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint program;
} cube_render_obj;