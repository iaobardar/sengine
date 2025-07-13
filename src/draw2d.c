#include <glad/gl.h>
#include <assert.h>
#include "buffer.h"

struct line_data {
    float* coords;
    size_t count;
    size_t capacity;
};

void clear_lines(struct line_data* lines)
{
    lines->count = 0;
}

void add_line(struct line_data* lines, float x, float y)
{
    size_t idx = lines->count;
    lines->count += 2;
    assert(grow_buffer((void**)&lines->coords, &lines->capacity, lines->count * sizeof(float)));
    lines->coords[idx]     = x;
    lines->coords[idx + 1] = y;
}

struct line_draw_buffers {
    size_t num_lines;
    unsigned int vao_handle;
    unsigned int vbo_handle;
};

void init_line_draw_buffers(struct line_draw_buffers* line_buffers)
{
    glGenVertexArrays(1, &line_buffers->vao_handle);
    glGenBuffers(1, &line_buffers->vbo_handle);
}

void update_line_draw_buffers(struct line_draw_buffers* line_buffers, struct line_data* lines)
{
    glBindBuffer(GL_ARRAY_BUFFER, line_buffers->vbo_handle);
    glBufferData(GL_ARRAY_BUFFER, lines->count * sizeof(GLfloat), lines->coords,  GL_DYNAMIC_DRAW);

    glBindVertexArray(line_buffers->vao_handle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
}

void draw_line_draw_buffers(struct line_draw_buffers* line_buffers)
{
    glDrawArrays(GL_LINE, 0, line_buffers->num_lines);
}