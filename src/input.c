typedef struct {
	double mouse_xpos;
	double mouse_ypos;
	double mouse_xvel;
	double mouse_yvel;

	int movement[4];
} input_record;

void get_input(GLFWwindow* window, input_record input)
{
	double new_xpos, new_ypos;
	glfwGetCursorPos(window, &new_xpos, &new_ypos);
	input.mouse_xvel = new_xpos - input.mouse_xpos;
	input.mouse_yvel = new_ypos - input.mouse_ypos;
	input.mouse_xpos = new_xpos;
	input.mouse_ypos = new_ypos;

	/*
	if (input.mouse_xvel != 0 || input.mouse_yvel != 0)
	{
		// the coords are origin in the upper left...
		camera.yaw -= input.mouse_xvel * 2 * dt;
		camera.pitch -= input.mouse_yvel * 2 * dt;
	}
	*/
	/*
	input.movement = {
		glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS,
		glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS,
	};
	*/
	
	/*
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
	}
	*/
}