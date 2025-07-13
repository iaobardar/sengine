#version 330 core

layout (location = 0) in vec4 vPosition;

uniform mat4 camera_transform;

void main()
{
    gl_Position = camera_transform * vPosition;
}

#--

#version 330 core

uniform mat4 camera_transform;

out vec4 fColor;

void main()
{
    float d = fwidth(gl_FragCoord.z);
    vec3 dx = vec3(d, 0, dFdx(gl_FragCoord.z));
    vec3 dy = vec3(0, d, dFdy(gl_FragCoord.z));
    vec3 normal = normalize(cross(dx, dy));

    vec3 light_pos = (camera_transform * vec4(3, 1, 2, 1)).xyz;
    float light = dot(normal, normalize(light_pos)) * .5 + .5;
    fColor = mix(vec4(0, 0, 0, 1.0), vec4(1, 1, 1, 1.0), light);
}