#include "glad/gl.h"
#include "vecmath.h"
#include "sstring.h"

typedef struct {
    float* vertices;
    size_t vertex_count;
    GLuint* indices;
    size_t index_count;
} mesh_container;

typedef struct {
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
} mesh_render_obj;

void init_meshrender_buffers(mesh_render_obj* obj)
{
    glGenVertexArrays(1, &obj->vao);
    glBindVertexArray(obj->vao);
    GLuint new_buffs[2];
    glGenBuffers(2, new_buffs);
    obj->vbo = new_buffs[0];
    obj->ibo = new_buffs[1];
}

void update_meshrender_data(mesh_render_obj* obj, const mesh_container* mesh)
{
    glBindVertexArray(obj->vao);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mesh->vertex_count, mesh->vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->index_count, mesh->indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
