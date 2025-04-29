#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include "sstring.h"
#include "math.h"
#include "sio.h"
#include "swindow.h"
#include "sshader.h"
#include "camera.h"

void check_gl_error(const char* operation) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error after %s: 0x%x\n", operation, error);
    }
}

struct {
	float fov;
} graphics_properties;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
	graphics_properties.fov = (float)height / (float)width;
}

void render()
{
	//printf("\e[1;1H\e[2J");
	//printf("(%f, %f, %f) : %f %f\n\n", camera.x, camera.y, camera.z, camera.yaw, camera.pitch);

	// CAMERA //

	vec3 cam_pos = {cos(time * 7 * .1), 1, cos(time * 5 * .1)};
	vec3 look = {0, 0, 0};
	mat4 camera_matrix;
	camera_lookat(cam_pos, look, camera_matrix, graphics_properties.fov);
	glUniformMatrix4fv(camera_mat_ul, 1, GL_TRUE, camera_matrix);

	// RENDER //

	float bg[] = {.1, .1, .1, .1};
	glClearBufferfv(GL_COLOR, 0, bg);

	glClearDepthf(2);
	glClear(GL_DEPTH_BUFFER_BIT);


	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, (GLvoid*)0);

}

void APIENTRY opengl_debug(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam) {
	fprintf(stdout, "OpenGL Debug Message: %s\n", message);
}

int main(int argc, char **argv)
{
	GLFWwindow* window = start_window("Graphics!");
	if (!window) return 1;

	// Load OpenGL
	assert(gladLoadGL(glfwGetProcAddress) > 0);	
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(opengl_debug, NULL);


	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
	    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	framebuffer_size_callback(window, &width, &height);

	// Load shaders
	if (argc < 2)
	{
		printf("Usage: %s <shader_file>\n", argv[0]);
		return 1;
	}
	shaderlistfile slf = load_shader_file(argv[1]);
	GLuint main_program = init_shader_program(&slf.shaders[0], &slf.shaders[1]);
	GLint camera_mat_ul = glGetUniformLocation(main_program, "camera_transform");
	assert(camera_mat_ul >= 0);



	glUseProgram(main_program);
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//glDepthRangef(0, 1);

	// Populate buffers
	GLfloat verts[] = {
		-.25, -.25, -.25,
		-.25,  .25, -.25,
		 .25,  .25, -.25,
		 .25, -.25, -.25,

		-.25, -.25,  .25,
		-.25,  .25,  .25,
		 .25,  .25,  .25,
		 .25, -.25,  .25,
	};

	#define quad(a, b, c, d) a, b, c, c, d, a

	GLushort indices[] = {
		quad(3, 2, 1, 0), // bottom

		quad(0, 1, 5, 4),
		quad(1, 2, 6, 5),
		quad(2, 3, 7, 6),
		quad(3, 0, 4, 7),

		quad(4, 5, 6, 7) //top
	};

	#undef quad

	enum {arraybuffer_i, indexbuffer_i, num_buffers};
	GLuint buffers[num_buffers];
	glCreateBuffers(num_buffers, buffers);

	glNamedBufferStorage(buffers[arraybuffer_i], sizeof(verts), verts, 0);
	glNamedBufferStorage(buffers[indexbuffer_i], sizeof(indices), indices, 0);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[arraybuffer_i]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[indexbuffer_i]);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	camera_rig camera = {.pitch = 3.1415 * .5, .z = .75, .y = 1};

	check_gl_error("start");

	double time = glfwGetTime();
	double dt = 0;
	int update_camera = 1;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
			continue;
		}

		double new_time = glfwGetTime();
		dt = new_time - time;
		time = new_time;


		glfwSwapBuffers(window);
	}

	check_gl_error("end");

	puts("Finished");
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}