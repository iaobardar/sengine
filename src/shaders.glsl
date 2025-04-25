#version 450 core

layout (location = 0) in vec4 vPosition;

uniform mat4 camera_transform;

void main()
{
	gl_Position = camera_transform * vPosition;
}

#--

#version 450 core

out vec4 fColor;
uniform vec4 fill_color;

void main()
{
	fColor = vec4(0.5, 0.2, 0.8, 1.0);
}