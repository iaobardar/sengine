#include <math.h>
#include <stdio.h>
#include "math.h"

static const mat4 IDENTITY_MATRIX = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

// Operations

// Vec 3

void vec3add(vec3 a, vec3 b, vec3 out)
{
	out[0] = a[0] + b[0];
	out[1] = a[1] + b[1];
	out[2] = a[2] + b[2];
}

void vec3sub(vec3 a, vec3 b, vec3 out)
{
	out[0] = a[0] - b[0];
	out[1] = a[1] - b[1];
	out[2] = a[2] - b[2];
}

void vec3scale(vec3 a, float s, vec3 out)
{
	out[0] = a[0] * s;
	out[1] = a[1] * s;
	out[2] = a[2] * s;
}

void vec3addip(vec3 a, vec3 b)
{
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

void vec3subip(vec3 a, vec3 b)
{
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

void vec3scaleip(vec3 a, float s)
{
	a[0] *= s;
	a[1] *= s;
	a[2] *= s;
}

float vec3dot(vec3 a, vec3 b)
{
	return a[0] * b[0]
	     + a[1] * b[1]
	     + a[2] + b[2];
}

float vec3length(vec3 a)
{
	return sqrt(vec3dot(a, a));
}

void vec3normip(vec3 a)
{
	vec3scaleip(a, 1 / vec3length(a));
}

void vec3cross(vec3 a, vec3 b, vec3 out)
{
	out[0] = a[1] * b[2] - a[2] * b[1];
	out[1] = a[2] * b[0] - a[0] * b[2];
	out[2] = a[0] * b[1] - a[1] * b[0]; 
}

// Mat 4

void mat4copy(const mat4 origin, mat4 target)
{
	for (int i = 0; i < 16; ++i)
		target[i] = origin[i];
}

void mat4mult(mat4 a, mat4 b, mat4 out)
{
	for (int r = 0; r < 4; ++r)
	for (int c = 0; c < 4; ++c)
	{
		out[r + 4 * c] = 0;
		for (int i = 0; i < 4; ++i)
			out[r + 4 * c] += a[r + 4 * i] * b[i + 4 * c];
	}
}

void mat4transform(mat4 transformation, mat4 target)
{
	mat4 temp;
	mat4mult(transformation, target, temp);
	mat4copy(temp, target);
}

// Print

void mat4print(mat4 in)
{
	for (int r = 0; r < 16; r+=4)
		printf("%2.2f, %2.2f, %2.2f, %2.2f\n", in[r], in[r + 1], in[r + 2], in[r + 3]);
}

void vec4print(vec4 in)
{
	printf("%2.2f, %2.2f, %2.2f, %2.2f\n", in[0], in[1], in[2], in[3]);
}

float vec4dot(vec4 a, vec4 b)
{
	return a[0] * b[0]
	     + a[1] * b[1]
	     + a[2] * b[2]
	     + a[3] * b[3];
}

void mat4multvec3(mat4 a, vec4 b, vec4 out)
{
	for (int r = 0; r < 4; ++r)
		out[r] = vec4dot(b, &a[4 * r]);
}

// Constructions

void mat4make_identity(mat4 a)
{
	mat4copy(IDENTITY_MATRIX, a);
}


void mat4make_translate(mat4 a, float x, float y, float z)
{
	mat4 translation = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1,
	};

	mat4copy(translation, a);
}

void mat4make_rotate(mat4 a, float yaw, float pitch)
{
	/*
		mat3 yaw_rotation = {
			cy, -sy, 0,
			sy,  cy, 0,
			 0,   0, 1,
		};

		mat3 pitch_rotation = {
			1,  0,   0,
			0, cp, -sp,
			0, sp,  cp,
		};
	*/

	float cy = cos(yaw);
	float sy = sin(yaw);

	float cp = cos(pitch);
	float sp = sin(pitch);

	mat4 rotation = {
		     cy,     -sy,   0, 0,
		cp * sy, cp * cy, -sp, 0,
		sp * sy, sp * cy,  cp, 0,
		      0,       0,   0, 1,
	};

	mat4copy(rotation, a);
}

void mat4make_perspective(mat4 a, float near, float far)
{
	mat4 perspective = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1,
	};
	mat4copy(perspective, a);
}
