#include "render_cube.h"
#include "assert.h"

static const GLfloat verts[] = {
    -1, -1, -1,
    -1,  1, -1,
     1,  1, -1,
     1, -1, -1,

    -1, -1,  1,
    -1,  1,  1,
     1,  1,  1,
     1, -1,  1,
};


static const GLushort indices[] = {
    #define quad(a, b, c, d) a, b, c, c, d, a
    quad(3, 2, 1, 0), // bottom

    quad(0, 1, 5, 4),
    quad(1, 2, 6, 5),
    quad(2, 3, 7, 6),
    quad(3, 0, 4, 7),

    quad(4, 5, 6, 7) //top
    #undef quad
};


void init_cube_render_obj(cube_render_obj* obj, mat4 model_matrix)
{
    glGenVertexArrays(1, &obj->vao);
    glBindVertexArray(obj->vao);

    glGenBuffers(1, &obj->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &obj->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //obj->model_matrix = model_matrix;
    //obj->program = program;

    assert(0);

    // Set up vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
