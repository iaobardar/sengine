#ifndef TEXTUREPACKING_H
#define TEXTUREPACKING_H

#include "texture.h"

struct sub_texture_info
{
   size_t x;
   size_t y;
   size_t width;
   size_t height;
};

struct packed_texture
{
   size_t count_sub_textures;
   struct sub_texture_info* sub_textures;
   struct texture container_texture;
};

struct packed_texture pack_textures(struct texture* textures, size_t count, size_t max_width);

#endif