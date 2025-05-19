#ifndef SWINDOW_H
#define SWINDOW_H

#include <GLFW/glfw3.h>

typedef struct {
    GLFWwindow* _glfw_window;
    double aspect_ratio;
} window_info;

window_info start_window(const char* name);
void tick_window(window_info* wnd);
void close_window(window_info* wnd);
int window_should_close(window_info* wnd);

#endif // SWINDOW_H