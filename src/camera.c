#include <stdio.h>
#include <math.h>
#include "camera.h"

void camera_set_angle(mat4 out, const vec3 org, float yaw, float pit)
{
    mat4 translate, orientation, perspective, temp;
	mat4_set_translate(translate, -org[0], -org[1], -org[2]);
	mat4_set_rotate(orientation, yaw, pit);
	mat4_set_perspective(perspective, .025, 20);

	mat4_mult(translate, orientation, temp);
    mat4_mult(temp, perspective, out);

	mat4_print(temp);
	putchar('\n');
	mat4_print(out);
	putchar('\n');
}

void camera_dir(const vec3 origin, const vec3 direction, float fov, mat4 out)
{
    const vec3 world_up = {0, 0, 1};

    vec3 forward, up, side;
    vec3_normalize(forward, direction);
    vec3_cross(forward, world_up, side);
    vec3_normalizeip(side);
    vec3_cross(side, forward, up);
    vec3_normalizeip(up);
}
