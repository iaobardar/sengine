#include <GLFW/glfw3.h>
#include "input.h"

frame_input_t init_inputs(const window_info* wnd)
{
    frame_input_t inputs = {0};
    inputs.time = glfwGetTime();
    return inputs;
}

void tick_inputs(const window_info* wnd, frame_input_t* inputs)
{
    double new_time = glfwGetTime();
    inputs->dt = new_time - inputs->time;
    inputs->time = new_time;

    double new_x, new_y;
    glfwGetCursorPos(wnd->_glfw_window, &new_x, &new_y);
    inputs->mouse_dx = new_x - inputs->mouse_x;
    inputs->mouse_dy = new_y - inputs->mouse_y;
    inputs->mouse_x = new_x;
    inputs->mouse_y = new_y;

    inputs->movement[0] = (glfwGetKey(wnd->_glfw_window, GLFW_KEY_D) == GLFW_PRESS ? 1.0 : 0.0)
                        - (glfwGetKey(wnd->_glfw_window, GLFW_KEY_A) == GLFW_PRESS ? 1.0 : 0.0);
    inputs->movement[1] = (glfwGetKey(wnd->_glfw_window, GLFW_KEY_W) == GLFW_PRESS ? 1.0 : 0.0)
                        - (glfwGetKey(wnd->_glfw_window, GLFW_KEY_S) == GLFW_PRESS ? 1.0 : 0.0);
}
