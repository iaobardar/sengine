#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <assert.h>
#include <stdio.h>

void LOG(char* msg)
{
	printf("\033[32m%s\033[0m\n", msg);
}

#include "src/sstring.c"
#include "src/sio.c"
#include "src/swindow.c"
#include "src/sshader.c"

int main(void)
{
	GLFWwindow* window = start_window("Graphics!");
	if (!window) return 1;

	assert(gladLoadGL(glfwGetProcAddress) > 0);

	shaderlistfile slf = load_shader_file("src/shaders.glsl");
	init_shader_program(&slf.shaders[0], &slf.shaders[1]);

	GLfloat verts[][2] = {
		{-.5, -.5},
		{  0,  .5},
		{ .5, -.5}
	};

	GLuint buffer;
	glCreateBuffers(1, &buffer);
	glNamedBufferStorage(buffer, sizeof(verts), verts, 0);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		float bg[] = {.1, .1, .1, .1};
		glClearBufferfv(GL_COLOR, 0, bg);

		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	puts("Worked!!");
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}