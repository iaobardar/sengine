#ifndef SSPRITE_H
#define SSPRITE_H

#include <stdint.h>
#include <assert.h>
#include "texturepacking.h"

struct sprite_list {
    float* positions;
    float* sizes;
    struct texture* textures;
    size_t count;
    size_t capacity;
    
    struct packed_texture combined_texture;

    uint8_t flags;

    uint32_t vao_handle;
    uint32_t frame_handle;
    uint32_t packedtex_handle;

    uint32_t ipos_handle;
    uint32_t iscale_handle;
    uint32_t iuv_handle;
};

/*
0: frame (same for all instances)
1: instance pos
2: instance scale
3: instance uv
*/

struct sprite_list init_sprite_list();

size_t new_sprite(struct sprite_list* sprites, float x, float y, float w, float h, struct texture* tex);
void set_sprite_position(struct sprite_list* sprites, size_t handle, float x, float y);
void set_sprite_size(struct sprite_list* sprites, size_t handle, float width, float height);
void set_sprite_texture(struct sprite_list* sprites, size_t handle, struct texture* tex);
void draw_sprites(struct sprite_list* sprites);

#endif