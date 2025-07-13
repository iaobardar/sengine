#include <assert.h>
#include <stdio.h>
#include "render_cube.h"
#include "sshader.h"

static const GLfloat cube_verts[] = {
    -.5, -.5, -.5,
    -.5,  .5, -.5,
     .5,  .5, -.5,
     .5, -.5, -.5,

    -.5, -.5,  .5,
    -.5,  .5,  .5,
     .5,  .5,  .5,
     .5, -.5,  .5,
};

static const GLushort cube_indices[] = {
    #define quad(a, b, c, d) a, b, c, c, d, a
    quad(3, 2, 1, 0), // bottom

    quad(0, 1, 5, 4),
    quad(1, 2, 6, 5),
    quad(2, 3, 7, 6),
    quad(3, 0, 4, 7),

    quad(4, 5, 6, 7) //top
    #undef quad
};

void create_cube_render_obj(cube_render_obj* cube)
{
    glGenVertexArrays(1, &cube->vao);
    glBindVertexArray(cube->vao);

    GLuint new_buffs[2];
    glGenBuffers(2, new_buffs);
    cube->vbo = new_buffs[0];
    cube->ibo = new_buffs[1];

    glBindBuffer(GL_ARRAY_BUFFER, cube->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_verts), cube_verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, (void*)0);

    shaderlistfile_t cube_shaders = load_shader_file("../resources/cube.glsl");
    assert(cube_shaders.count >= 2);
    cube->program = init_shader_program(&cube_shaders.shaders[0], &cube_shaders.shaders[1]);
    assert(cube->program != 0);
}

void draw_cube(cube_render_obj* cube, mat4 camera_transform)
{
    glUseProgram(cube->program);
    GLint camera_mat_ul = glGetUniformLocation(cube->program, "camera_transform");
    glUniformMatrix4fv(camera_mat_ul, 1, GL_TRUE, (const GLfloat*)camera_transform);
    glBindVertexArray(cube->vao);
    glDrawElements(GL_TRIANGLES, sizeof(cube_indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, (void*)0);
}
