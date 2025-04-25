#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <assert.h>
#include <stdio.h>
#include <math.h>

void LOG(char* msg)
{
	printf("\033[32m%s\033[0m\n", msg);
}

#include "src/arrays.c"

#include "src/sstring.c"
#include "src/sio.c"
#include "src/swindow.c"
#include "src/sshader.c"

#include "src/meth.c"

void check_gl_error(const char* operation) {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error after %s: 0x%x\n", operation, error);
    }
}

int main(void)
{
	GLFWwindow* window = start_window("Graphics!");
	if (!window) return 1;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwRawMouseMotionSupported())
	    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

	// Load GL
	assert(gladLoadGL(glfwGetProcAddress) > 0);


	// Load shaders
	shaderlistfile slf = load_shader_file("src/shaders.glsl");
	GLuint main_program = init_shader_program(&slf.shaders[0], &slf.shaders[1]);

	GLint camera_mat_ul = glGetUniformLocation(main_program, "camera_transform");
	assert(camera_mat_ul >= 0);
	//GLint fill_color_ul = glGetUniformLocation(main_program, "fill_color");
	//assert(fill_color_ul >= 0);

	glUseProgram(main_program);


	// Populate buffers
	GLfloat verts[][2] = {
		{-.5, -.5},
		{  0,  .5},
		{ .5, -.5}
	};

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	GLuint buffer;
	glCreateBuffers(1, &buffer);
	glNamedBufferStorage(buffer, sizeof(verts), verts, 0);
	
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	mat4 camera_matrix = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};

	glUniformMatrix4fv(camera_mat_ul, 1, GL_TRUE, camera_matrix);

	check_gl_error("start");

	double time = glfwGetTime();
	double dt = 0;

	while (!glfwWindowShouldClose(window))
	{
		double new_time = glfwGetTime();
		dt = new_time - time;
		time = new_time;

		//float fc[] = {.1, sin(time) * .5 + .5, .1, 1};
		//vec4print(fc);
		//glProgramUniform4fv(main_program, 0, 1, fc);


		float bg[] = {.1, .1, .1, .1};
		glClearBufferfv(GL_COLOR, 0, bg);


		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glfwSwapBuffers(window);
		glfwPollEvents();

		int input[] = {
			glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS,
			glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS,
		};

		if (input[0] || input[1])
		{
			mat4translate(camera_matrix, 0, input[0] && !input[1] ? .1 * dt : -.1 * dt, 0);
			glUniformMatrix4fv(camera_mat_ul, 1, GL_TRUE, camera_matrix);

			mat4print(camera_matrix);
			putchar('\n');
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		    glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}

	puts("Finished");
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}