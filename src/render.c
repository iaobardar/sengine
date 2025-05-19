#include "render.h"
#include "sshader.h"

// this provides a way to represent some renderable object.

/*
render_obj_t create_render_object()
{
    render_obj_t obj = {0};
    
    glGenVertexArrays(1, &obj.vao);
    glBindVertexArray(obj.vao);

    glCreateBuffers(1, &obj.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj.vbo);

    glCreateBuffers(1, &obj.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj.ibo);

    return obj;
}

void add_program_to_object(render_obj_t* obj, sstring* vertex_shader, sstring* fragment_shader)
{
    obj->program = init_shader_program(vertex_shader, fragment_shader);
}

void add_geometry_to_object(render_obj_t* obj, GLuint* buffers, size_t count)
{
    glCreateBuffers(count, buffers);
    obj->vbo = buffers[0];
    obj->ibo = buffers[1];

    //glNamedBufferStorage(obj->vbo, sizeof(verts), verts, 0);
    
}

void render_object(GLFWwindow* window, render_obj_t* to_render, camera_t* camera)
{
    //printf("\e[1;1H\e[2J");

    // CAMERA //

    glUniformMatrix4fv(camera_mat_ul, 1, GL_TRUE, camera_matrix);

    // RENDER //

    float bg[] = {.1, .1, .1, .1};
    glClearBufferfv(GL_COLOR, 0, bg);

    glClearDepthf(2);
    glClear(GL_DEPTH_BUFFER_BIT);

    glUseProgram(scene->program);
    glBindVertexArray(scene->vao);
    //sizeof(indices) / sizeof(GLushort)
    glDrawElements(GL_TRIANGLES, scene->geo_count, GL_UNSIGNED_SHORT, (GLvoid*)0);

}
*/