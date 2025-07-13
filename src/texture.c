#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "texture.h"

struct texture load_texture(char* path)
{
    stbi_set_flip_vertically_on_load(1);
    int width, height, nrChannels;
    void* data = stbi_load(path, &width, &height, &nrChannels, 4);
    assert(data);
    return (struct texture){.width = width, .height = height, .data = data};
}