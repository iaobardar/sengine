#version 330 core

layout (location = 0) in vec4 vPosition;

uniform mat4 camera_transform;

void main()
{
	gl_Position = camera_transform * vPosition;
}

#--

#version 330 core

out vec4 fColor;
uniform vec4 fill_color;

void main()
{
	fColor = mix(vec4(0, 1, 0, 1.0), vec4(1, 1, 1, 1.0), gl_FragCoord.z);
}