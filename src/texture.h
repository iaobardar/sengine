#ifndef TEXTURE_H
#define TEXTURE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct texture {
    size_t width;
    size_t height;
    uint8_t* data;
};

struct texture load_texture(char* path);

static inline void fill_texture(struct texture* tex, int value)
{
    memset(tex->data, value, tex->width * tex->height * sizeof(uint64_t));
}

static inline struct texture alloc_texture(size_t width, size_t height)
{
    void* x = malloc(width * height * 4 * sizeof(uint8_t));
    assert(x);
    return (struct texture){.width = width, .height = height, .data = x};
}

static inline struct texture copy_texture(struct texture* tex)
{
    struct texture x = alloc_texture(tex->width, tex->height);
    memcpy(x.data, tex->data, tex->width * tex->height * 4 * sizeof(uint8_t));
    return x;
}

static inline void blit_texture(size_t width, size_t height, struct texture* dst, size_t dst_x, size_t dst_y, struct texture* src, size_t src_x, size_t src_y)
{
    if (src->width - src_x < width) width = src->width - src_x;
    if (dst->width - dst_x < width) width = dst->width - dst_x;

    if (src->height - src_y < height) height = src->height - src_y;
    if (dst->height - dst_y < height) height = dst->height - dst_y;

    for (size_t yi = 0; yi < height; ++yi)
    {        
        size_t src_i = src_x + (src_y + yi) * src->width;
        size_t dst_i = dst_x + (dst_y + yi) * dst->width;

        memcpy(&dst->data[dst_i * 4], &src->data[src_i * 4], width * 4 * sizeof(uint8_t));
    }
}

#endif