#include <stdio.h>
#include "swindow.h"

GLFWwindow* start_window(const char* name)
{
	if (!glfwInit()) return 0;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(640, 480, name, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return 0;
	}
	
	glfwMakeContextCurrent(window);
	puts("success starting window");
	return window;
}