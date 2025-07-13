#include "glad/gl.h"
#include "vecmath.h"

typedef struct {
    //mat4 model_matrix;
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint program;
} cube_render_obj;

void create_cube_render_obj(cube_render_obj* obj);
void draw_cube(cube_render_obj* cube, mat4 camera_transform);
