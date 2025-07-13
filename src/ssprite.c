#include <assert.h>
#include <stdlib.h>
#include <glad/gl.h>
#include <stdio.h>
#include "ssprite.h"
#include "sshader.h"

enum SPRITE_FLAGS {
    DIRTY_POSITIONS,
    DIRTY_SCALES,
    DIRTY_TEXTURES,
};

enum VAA_INDICES {
    VAA_FRAME = 0,
    VAA_IPOS,
    VAA_ISCALE,
    VAA_IUV,
};

static GLuint SPRITE_PROGRAM = 0;
static GLuint SPRITE_TEXTUREPACK_UL = 0;

struct sprite_list init_sprite_list()
{
    struct sprite_list new = {0};

    shaderlistfile_t sprite_shaders = load_shader_file("../resources/sprite.glsl");
    assert(sprite_shaders.count >= 2);
    SPRITE_PROGRAM = init_shader_program(&sprite_shaders.shaders[0], &sprite_shaders.shaders[1]);
    SPRITE_TEXTUREPACK_UL = glGetUniformLocation(SPRITE_PROGRAM, "texturepack");

    // gen all the needed gpu storage.
    glGenVertexArrays(1, &new.vao_handle);
    glGenTextures(1, &new.packedtex_handle);
    
    uint32_t buffs[4];
    glGenBuffers(4, buffs);
    new.frame_handle   = buffs[0];
    new.ipos_handle    = buffs[1];
    new.iscale_handle  = buffs[2];
    new.iuv_handle     = buffs[3];

    glBindVertexArray(new.vao_handle);

    glEnableVertexAttribArray(VAA_FRAME);
    glEnableVertexAttribArray(VAA_IPOS);
    glEnableVertexAttribArray(VAA_ISCALE);
    glEnableVertexAttribArray(VAA_IUV);
    glVertexAttribDivisor(VAA_IPOS,   1);
    glVertexAttribDivisor(VAA_ISCALE, 1);
    glVertexAttribDivisor(VAA_IUV,    1);

    // set up the static frame:
    static const float frame_verts[] = {
        0, 0,
        0, 1,
        1, 0,
        1, 1,
    };
    glBindBuffer(GL_ARRAY_BUFFER, new.frame_handle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(frame_verts), frame_verts, GL_STATIC_DRAW);
    glVertexAttribPointer(VAA_FRAME, 2, GL_FLOAT, 0, 0, (void*)0);

    return new;

    /*
    glBindBuffer(GL_ARRAY_BUFFER, SPRITE_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0); // Locations
    glEnableVertexAttribArray(1); // Texture Coords

    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 4 * sizeof(GLfloat), 0);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
    */

    /*
    glGenTextures(1, &SPRITE_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, SPRITE_TEXTURE);
    int width, height, nrChannels;
    void* data = stbi_load("../resources/sample.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    */
}

size_t new_sprite(struct sprite_list* sprites, float x, float y, float w, float h, struct texture* tex)
{
    assert(tex);

    size_t idx = sprites->count++;

    size_t to_allocate = (sprites->capacity > 2) ? sprites->capacity : 2;
    while(sprites->count > to_allocate)
        to_allocate += to_allocate >> 1;

    assert(to_allocate >= sprites->capacity); // integer overflow check

    sprites->positions = realloc(sprites->positions, to_allocate * 2 * sizeof(float));
    sprites->sizes     = realloc(sprites->sizes,     to_allocate * 2 * sizeof(float));
    sprites->textures  = realloc(sprites->textures,  to_allocate * sizeof(struct texture));
    
    assert(sprites->positions && sprites->sizes && sprites->textures);

    sprites->capacity = to_allocate;

    set_sprite_position(sprites, idx, x, y);
    set_sprite_size(sprites, idx, w, h);
    set_sprite_texture(sprites, idx, tex);

    return idx;
}

void set_sprite_position(struct sprite_list* sprites, size_t handle, float x, float y)
{
    assert(handle < sprites->count && handle < sprites->capacity);
    sprites->positions[handle * 2]     = x;
    sprites->positions[handle * 2 + 1] = y;

    sprites->flags |= (1 << DIRTY_POSITIONS);
}

void set_sprite_size(struct sprite_list* sprites, size_t handle, float width, float height)
{
    assert(handle < sprites->count && handle < sprites->capacity);
    sprites->sizes[handle * 2]     = width;
    sprites->sizes[handle * 2 + 1] = height;

    sprites->flags |= (1 << DIRTY_SCALES);
}

void set_sprite_texture(struct sprite_list* sprites, size_t handle, struct texture* tex)
{
    assert(handle < sprites->count && handle < sprites->capacity);
    sprites->textures[handle] = copy_texture(tex);

    sprites->flags |= (1 << DIRTY_TEXTURES);
}

void draw_sprites(struct sprite_list* sprites)
{
    glBindVertexArray(sprites->vao_handle);

    if (sprites->flags & (1 << DIRTY_POSITIONS))
    {
        sprites->flags &= ~(1 << DIRTY_POSITIONS);

        glBindBuffer(GL_ARRAY_BUFFER, sprites->ipos_handle);
        glBufferData(GL_ARRAY_BUFFER, sprites->count * 2 * sizeof(float), sprites->positions, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(VAA_IPOS, 2, GL_FLOAT, 0, 0, (void*)0);
    }

    if (sprites->flags & (1 << DIRTY_SCALES))
    {
        sprites->flags &= ~(1 << DIRTY_SCALES);

        glBindBuffer(GL_ARRAY_BUFFER, sprites->iscale_handle);
        glBufferData(GL_ARRAY_BUFFER, sprites->count * 2 * sizeof(float), sprites->sizes, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(VAA_ISCALE, 2, GL_FLOAT, 0, 0, (void*)0);
    }

    glActiveTexture(GL_TEXTURE0);

    if (sprites->flags & (1 << DIRTY_TEXTURES))
    {
        sprites->flags &= ~(1 << DIRTY_TEXTURES);
        
        struct packed_texture pt = pack_textures(sprites->textures, sprites->count, 1028 << 3);
        sprites->combined_texture = pt;
        float width  = (float)pt.container_texture.width;
        float height = (float)pt.container_texture.height;
        size_t uvs_alloc = sprites->count * 4 * sizeof(float);
        float* uvs = malloc(uvs_alloc);

        puts("Packing Textures:");
        for (size_t i = 0; i < sprites->count; ++i)
        {
            size_t idx = i * 4;
            uvs[idx + 0] = sprites->combined_texture.sub_textures[i].x / width;
            uvs[idx + 1] = sprites->combined_texture.sub_textures[i].y / height;
            uvs[idx + 2] = sprites->combined_texture.sub_textures[i].width  / width;
            uvs[idx + 3] = sprites->combined_texture.sub_textures[i].height / height;

            printf("%zu: %f,%f:%f,%f\n", i, uvs[idx + 0], uvs[idx + 1], uvs[idx + 2], uvs[idx + 3]);
        }

        glBindBuffer(GL_ARRAY_BUFFER, sprites->iuv_handle);
        glBufferData(GL_ARRAY_BUFFER, uvs_alloc, uvs, GL_DYNAMIC_DRAW);
        glVertexAttribPointer(VAA_IUV, 4, GL_FLOAT, 0, 0, 0);

        glBindTexture(GL_TEXTURE_2D, sprites->packedtex_handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pt.container_texture.width, pt.container_texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pt.container_texture.data);
        glGenerateMipmap(GL_TEXTURE_2D);

        free(uvs);
    }

    glUseProgram(SPRITE_PROGRAM);
    
    glBindTexture(GL_TEXTURE_2D, sprites->packedtex_handle);
    glUniform1i(SPRITE_TEXTUREPACK_UL, 0);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, sprites->count);
}