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

int main(int argc, char **argv)
{

    /*
    shaderlistfile_t slf = load_shader_file(argv[1]);
    GLuint main_program = init_shader_program(&slf.shaders[0], &slf.shaders[1]);
    GLint camera_mat_ul = glGetUniformLocation(main_program, "camera_transform");
    assert(camera_mat_ul >= 0);

    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glDepthRangef(0, 1);
    */

    window_info window = start_window("Graphics!");
    frame_input_t input = init_inputs(&window);

    struct {
        vec3 pos; float yaw; float pitch;
    } player;
    player.pos[0]=0;
    player.pos[1]=0;
    player.pos[2]=0;
    player.yaw = 0;
    player.pitch = 3.1415 / 2.0;
    
    tick_window(&window);
    tick_inputs(&window, &input);

    while (!window_should_close(&window))
    {
        tick_window(&window);
        tick_inputs(&window, &input);

        if (input.mouse_dx != 0.0 || input.mouse_dy != 0.0)
        {
            player.yaw   += input.mouse_dx * input.dt;
            //player.pitch += input.mouse_dy * input.dt;
            
            mat4 tlt, rot, camera;
            mat4_set_translate(tlt, 0, -1, 0);
            mat4_set_rotate(rot, player.yaw, player.pitch);
            mat4_mult(camera, rot, tlt);

            printf("\n\n(%f, %f)\n", player.yaw, player.pitch);
            mat4_print(camera);

            vec4 sample;
            vec4 x = {0, 0, 0, 1};
            mat4_mult_vec4(sample, camera, x);
            vec4_print(sample);
        }
    }

    close_window(&window);
    return 0;
}