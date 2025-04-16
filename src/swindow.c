GLFWwindow* start_window(const char* name)
{
	if (!glfwInit()) return 0;
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