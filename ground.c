#include "ground.h"

float perlin_noise(int seed, float x, float y)
{
    // Simplex noise or Perlin noise implementation would go here.
    // For now, we will just return a simple function of x and y.
    return sinf(x * 7) * cosf(y * 5);
}

void init_ground(ground_render_obj* obj, uint32_t width, uint32_t height)
{
    // GEOMETRY INITIALIZATION

    glGenVertexArrays(1, &obj->vao);
    glBindVertexArray(obj->vao);

    size_t size_verts = sizeof(float) * 3 * width * height;
    float* verts = malloc(size_verts);
    assert(verts != NULL);

    for (uint32_t y = 0; y < height; ++y)
        for (uint32_t x = 0; x < width; ++x)
        {
            float fx = (float)x / (width - 1);
            float fy = (float)y / (height - 1);
            float fz = perlin_noise(1947, fx, fy);

            verts[3 * (y * width + x) + 0] = fx;
            verts[3 * (y * width + x) + 1] = fy;
            verts[3 * (y * width + x) + 2] = fz;
        }
    
    glGenBuffers(1, &obj->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, obj->vbo);
    glBufferData(GL_ARRAY_BUFFER, size_verts, verts, GL_STATIC_DRAW);
    free(verts);

    size_t size_indices = sizeof(GLushort) * 6 * width * height;
    GLushort* indices = malloc(size_indices);
    assert(indices != NULL);

    for (uint32_t y = 0; y < height - 1; ++y)
        for (uint32_t x = 0; x < width - 1; ++x)
        {
            size_t i = y * width + x;
            size_t ii = 6 * i;

            indices[ii + 0] = i;
            indices[ii + 1] = i + 1;
            indices[ii + 2] = i + width;

            indices[ii + 3] = i + 1;
            indices[ii + 4] = i + 1 + width;
            indices[ii + 5] = i + width;
        }

    glGenBuffers(1, &obj->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, obj->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size_indices, indices, GL_STATIC_DRAW);
    free(indices);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void render_ground(ground_render_obj *obj, mat4 camera_matrix)
{
    glUseProgram(obj->program);
    glUniformMatrix4fv(0, 1, GL_TRUE, camera_matrix);

    glBindVertexArray(obj->vao);
    glDrawElements(GL_TRIANGLES, obj->element_count, GL_UNSIGNED_SHORT, (void*)0); // Assuming 6 vertices for the ground
    glBindVertexArray(0);
}