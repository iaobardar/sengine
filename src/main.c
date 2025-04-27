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

void APIENTRY opengl_debug(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar* message, const void* userParam) {
	fprintf(stdout, "OpenGL Debug Message: %s\n", message);
}

int main(int argc, char **argv)
{
	GLFWwindow* window = start_window("Graphics!");
	if (!window) return 1;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
	    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	// Load GL
	assert(gladLoadGL(glfwGetProcAddress) > 0);
	printf("OpenGL version: %s\n", glGetString(GL_VERSION));
	printf("GLSL version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(opengl_debug, NULL);

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
	//GLint fill_color_ul = glGetUniformLocation(main_program, "fill_color");
	//assert(fill_color_ul >= 0);

	glUseProgram(main_program);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_GREATER);
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
	{
		mat4 camera_matrix;
		make_camera_matrix(&camera, camera_matrix);
		glUniformMatrix4fv(camera_mat_ul, 1, GL_TRUE, camera_matrix);
	}

	check_gl_error("start");

	double time = glfwGetTime();
	double dt = 0;

	while (!glfwWindowShouldClose(window))
	{
		{
			double new_time = glfwGetTime();
			dt = new_time - time;
			time = new_time;
		}

		//float fc[] = {.1, sin(time) * .5 + .5, .1, 1};
		//vec4print(fc);
		//glProgramUniform4fv(main_program, 0, 1, fc);


		float bg[] = {.1, .1, .1, .1};
		glClearBufferfv(GL_COLOR, 0, bg);


		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(GLushort), GL_UNSIGNED_SHORT, (GLvoid*)0);


		glfwSwapBuffers(window);
		glfwPollEvents();

		{
			double mouse_xpos, mouse_ypos, mouse_xvel, mouse_yvel;

			{
				double new_xpos, new_ypos;
				glfwGetCursorPos(window, &new_xpos, &new_ypos);
				mouse_xvel = new_xpos - mouse_xpos;
				mouse_yvel = new_ypos - mouse_ypos;
				mouse_xpos = new_xpos;
				mouse_ypos = new_ypos;
			}

			int input[] = {
				glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS,
				glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS,
				glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS,
				glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS,
			};

			int camera_changed = 0;
			if (mouse_xvel != 0 || mouse_yvel != 0)
			{
				// the coords are origin in the upper left...
				camera.yaw -= mouse_xvel * 2 * dt;
				camera.pitch -= mouse_yvel * 2 * dt;
				camera_changed = 1;
			}

			if (input[0] || input[1] || input[2] || input[3])
			{
				float forward = input[0] || input[1]
				                ? (input[0] && !input[1] ? dt : -dt)
				                : 0;

				float lateral = input[3] || input[2]
				                ? (input[3] && !input[2] ? dt : -dt)
				                : 0;

				float c = cos(camera.yaw);
				float s = sin(camera.yaw);

				camera.y += forward * c + lateral * -s;
				camera.x += forward * s + lateral * c;

				camera_changed = 1;
			}

			if (camera_changed)
			{
				printf("\e[1;1H\e[2J");
				printf("(%f, %f, %f) : %f %f\n", camera.x, camera.y, camera.z, camera.yaw, camera.pitch);
				mat4 camera_matrix;
				make_camera_matrix(&camera, camera_matrix);
				glUniformMatrix4fv(camera_mat_ul, 1, GL_TRUE, camera_matrix);

				mat4print(camera_matrix);
				putchar('\n');

				vec4 x = {0,0,0,0};
				vec4 result;
				mat4multvec3(camera_matrix, x, result);
				vec4print(result);
				putchar('\n');
			}

			if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			    glfwSetWindowShouldClose(window, GLFW_TRUE);
			}
		}
	}

	check_gl_error("end");

	puts("Finished");
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}