#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "camera.h"
#include "sstring.h"

typedef struct {
    GLuint program;
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    GLuint count;
} render_obj_t;

void add_program_to_object(render_obj_t* obj, sstring* vertex_shader, sstring* fragment_shader);
void render_object(GLFWwindow* window, render_obj_t* to_render, camera_t* camera);
