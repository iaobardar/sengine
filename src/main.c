#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "input.h"
#include "sio.h"
#include "swindow.h"
#include "camera.h"
#include "ssprite.h"

int main(int argc, char **argv)
{
    window_info window = start_window("Graphics!");
    frame_input_t input = init_inputs(&window);

    struct {
        vec3 pos; float yaw; float pitch;
    } player = {0};
    player.pitch = 3.1415 / 2.0;

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glDepthRange(0, 1);
    glDepthFunc(GL_LESS);
    glClearColor(0.81, 0.8, 0.83, 1.0);
    glClearDepth(1.0);

    struct sprite_list lol = init_sprite_list();
    struct texture t0 = load_texture("C:/Users/iaoba/OneDrive/Pictures/EPJk8ytWoAEeppc.jpg");
    struct texture t2 = load_texture("C:/Users/iaoba/OneDrive/Pictures/Fh56NRRX0AAAELg.jpg");
    struct texture t1 = load_texture("C:/Users/iaoba/OneDrive/Pictures/FlM6edFaAAAr3ES.png");
    new_sprite(&lol, 0, 0, 1, 1, &t0);
    new_sprite(&lol, 0, 0, .2, .8, &t1);
    new_sprite(&lol, .5, .1, .8, .2, &t2);

    printf("sprite count: %zu(of %zu bytes):[", lol.count, lol.capacity);
    for (size_t i = 0; i < lol.count * 2; ++i)
    {
        printf("(%f) ", ((float*)lol.positions)[i]);
    }
    puts("]");
    printf("sprite count: %zu(of %zu bytes):[", lol.count, lol.capacity);
    for (size_t i = 0; i < lol.count * 2; ++i)
    {
        printf("(%f) ", ((float*)lol.sizes)[i]);
    }
    puts("]");

    tick_window(&window);
    tick_inputs(&window, &input);

    mat4 camera;
    mat4_set_identity(camera);

    while (!window_should_close(&window))
    {
        tick_window(&window);
        tick_inputs(&window, &input);

        /*
        if (input.mouse_dx != 0.0 || input.mouse_dy != 0.0 || input.movement[0] != 0.0 || input.movement[1] != 0.0)
        {
            player.yaw   -= input.mouse_dx * input.dt * 0.1f;
            player.pitch -= input.mouse_dy * input.dt * 0.1f;
            float y_input = input.movement[1] * input.dt * 1.5f;
            float x_input = input.movement[0] * input.dt * 1.5f;
            float s = sinf(player.yaw);
            float c = cosf(player.yaw);
            player.pos[0] += x_input * c - y_input * s;
            player.pos[1] += x_input * s + y_input * c;

            mat4 move, rot, perspective, temp;
            mat4_set_translate(move, -player.pos[0], -player.pos[1], -player.pos[2]);
            mat4_set_rotate(rot, -player.yaw, -player.pitch);
            mat4_set_perspective(perspective, .01, 10);

            mat4_mult(temp, perspective, rot);
            mat4_mult(camera, temp, move);

            printf("\n\n(%f, %f, %f) : (%f, %f)\n", player.pos[0], player.pos[1], player.pos[2], player.yaw, player.pitch);
            mat4_print(camera);
            putchar('\n');

            vec4 sample;
            vec4 x = {0, 0, 0, 1};
            mat4_mult_vec4(sample, camera, x);
            vec4_print(sample);

            vec4 y = {0, 0, 1, 1};
            mat4_mult_vec4(sample, camera, y);
            vec4_print(sample);
        }
            */
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //draw_cube(&cube, camera);
        draw_sprites(&lol);
    }

    close_window(&window);
    return 0;
}