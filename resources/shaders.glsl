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

uint rand(uint x)
{
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return x;
}

void main()
{
    float d = fwidth(gl_FragCoord.z);
    vec3 dx = vec3(d, 0, dFdx(gl_FragCoord.z));
    vec3 dy = vec3(0, d, dFdy(gl_FragCoord.z));
    vec3 normal = normalize(cross(dx, dy));
    float light = dot(normal, normalize(vec3(1, 1, 1))) * .5 + .5;
    fColor = mix(vec4(0, 0, 0, 1.0), vec4(1, 1, 1, 1.0), light);
}