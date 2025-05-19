#include <stdio.h>
#include <assert.h>
#include <glad/gl.h>
#include "swindow.h"

void GLAPIENTRY opengl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
    GLsizei length, const GLchar* message, const void* userParam) {
    printf("OpenGL Debug Message: %s\n", message);
}

void update_window_aspect_ratio(window_info* wnd)
{
    int width, height;
    glfwGetFramebufferSize(wnd->_glfw_window, &width, &height);

    glViewport(0, 0, width, height);
    wnd->aspect_ratio = (double)height / (double)width;
}

window_info start_window(const char* name)
{
    assert(glfwInit());
    window_info wnd = {0};

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    wnd._glfw_window = glfwCreateWindow(640, 480, name, NULL, NULL);
    assert(wnd._glfw_window);
    
    glfwMakeContextCurrent(wnd._glfw_window);

    assert(gladLoadGL(glfwGetProcAddress) > 0);    
    printf("OpenGL version: %s\n", glGetString(GL_VERSION));
    printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    if (glDebugMessageCallback) {
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(opengl_debug_callback, NULL);
        puts("OpenGL debug output enabled.");
    } else {
        puts("OpenGL debug output not supported.");
    }

    glfwSetInputMode(wnd._glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
        glfwSetInputMode(wnd._glfw_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);


    update_window_aspect_ratio(&wnd);
    puts("success starting window");
    return wnd;
}

void tick_window(window_info* wnd)
{
    glfwSwapBuffers(wnd->_glfw_window);
    glfwPollEvents();

    if (glfwGetKey(wnd->_glfw_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(wnd->_glfw_window, GLFW_TRUE);
        return;
    }

    update_window_aspect_ratio(wnd);
}

void close_window(window_info* wnd)
{
    puts("Finished");
    glfwDestroyWindow(wnd->_glfw_window);
    glfwTerminate();
}

int window_should_close(window_info* wnd)
{
    return glfwWindowShouldClose(wnd->_glfw_window);
}
