#ifndef VECMATH_H
#define VECMATH_H

#include <math.h>
#include <stdio.h>

// Type definitions
typedef float mat4[16];
typedef float mat3[9];
typedef float vec4[4];
typedef float vec3[3];

// DECLARATIONS:

// Vec3 operations
static inline void vec3_add(vec3 out, const vec3 a, const vec3 b);
static inline void vec3_sub(vec3 out, const vec3 a, const vec3 b);
static inline void vec3_scale(vec3 out, const vec3 a, float s);
static inline void vec3_normalize(vec3 out, const vec3 in);

static inline void vec3_cross(vec3 out, const vec3 a, const vec3 b);
static inline float vec3_dot(const vec3 a, const vec3 b);
static inline float vec3_length(const vec3 a);

static inline void vec3_addip(vec3 a, const vec3 b);
static inline void vec3_subip(vec3 a, const vec3 b);
static inline void vec3_scaleip(vec3 a, float s);
static inline void vec3_normalizeip(vec3 a);

// Mat3 operations
static inline void mat3_set(mat3 target, const mat3 origin);
static inline void mat3_mult(mat3 out, const mat3 a, const mat3 b);
static inline void mat3_to_mat4(mat4 out, const mat3 in);

// Vec4 operations
static inline void vec4_scaleip(vec4 a, float scale);
static inline float vec4_dot(const vec4 a, const vec4 b);

// Mat4 operations
static inline void mat4_set(mat4 target, const mat4 origin);
static inline void mat4_mult(mat4 out, const mat4 a, const mat4 b);
static inline void mat4_mult_vec4(vec4 out, const mat4 a, const vec4 b);

// Mat4 constructions
static inline void mat4_set_identity(mat4 a);
static inline void mat4_set_translate(mat4 a, float x, float y, float z);
static inline void mat4_set_rotate(mat4 out, float yaw, float pitch);
static inline void mat4_set_perspective(mat4 a, float near, float far);

// Print functions
static inline void mat4_print(mat4 in);
static inline void vec4_print(vec4 in);
static inline void vec3_print(vec3 in);

// DEFINITIONS:

static inline void vec3_add(vec3 out, const vec3 a, const vec3 b)
{
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

static inline void vec3_sub(vec3 out, const vec3 a, const vec3 b)
{
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

static inline void vec3_scale(vec3 out, const vec3 a, float s)
{
    out[0] = a[0] * s;
    out[1] = a[1] * s;
    out[2] = a[2] * s;
}

static inline void vec3_addip(vec3 a, const vec3 b)
{
    a[0] += b[0];
    a[1] += b[1];
    a[2] += b[2];
}

static inline void vec3_subip(vec3 a, const vec3 b)
{
    a[0] -= b[0];
    a[1] -= b[1];
    a[2] -= b[2];
}

static inline void vec3_scaleip(vec3 a, float s)
{
    a[0] *= s;
    a[1] *= s;
    a[2] *= s;
}

static inline float vec3_dot(const vec3 a, const vec3 b)
{
    return a[0] * b[0]
         + a[1] * b[1]
         + a[2] + b[2];
}

static inline float vec3_length(const vec3 a)
{
    return sqrt(vec3_dot(a, a));
}

static inline void vec3_normalizeip(vec3 a)
{
    float frac = 1 / vec3_length(a);
    vec3_scaleip(a, frac);
}

static inline void vec3_normalize(vec3 out, const vec3 in)
{
    float frac = 1 / vec3_length(in);
    vec3_scale(out, in, frac);
}

static inline void vec3_cross(vec3 out, const vec3 a, const vec3 b)
{
    out[0] = a[1] * b[2] - a[2] * b[1];
    out[1] = a[2] * b[0] - a[0] * b[2];
    out[2] = a[0] * b[1] - a[1] * b[0];
}

// Vec 4

static inline void vec4_scaleip(vec4 a, float scale)
{
    a[0] *= scale;
    a[1] *= scale;
    a[2] *= scale;
    a[3] *= scale;
}

static inline float vec4_dot(const vec4 a, const vec4 b)
{
    return a[0] * b[0]
         + a[1] * b[1]
         + a[2] * b[2]
         + a[3] * b[3];
}

// Mat 3
static inline void mat3_set(mat3 target, const mat3 origin)
{
    for (int i = 0; i < 9; ++i)
        target[i] = origin[i];
}

static inline void mat3_mult(mat3 out, const mat3 a, const mat3 b)
{
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            out[row + 3 * col] = a[3 * col + 0] * b[3 * 0 + row]
                               + a[3 * col + 1] * b[3 * 1 + row]
                               + a[3 * col + 2] * b[3 * 2 + row];
}

static inline void mat3_to_mat4(mat4 out, const mat3 in)
{
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    out[3] = 0;

    out[4] = in[3];
    out[5] = in[4];
    out[6] = in[5];
    out[7] = 0;

    out[8] = in[6];
    out[9] = in[7];
    out[10] = in[8];
    out[11] = 0;

    out[12] = 0;
    out[13] = 0;
    out[14] = 0;
    out[15] = 1;
}

// Mat 4

static inline void mat4_set(mat4 target, const mat4 origin)
{
    for (int i = 0; i < 16; ++i)
        target[i] = origin[i];
}

static inline void mat4_mult(mat4 out, const mat4 a, const mat4 b)
{
    for (int row = 0; row < 4; ++row)
        for (int col = 0; col < 4; ++col)
            out[row + 4 * col] = a[4 * col + 0] * b[4 * 0 + row]
                               + a[4 * col + 1] * b[4 * 1 + row]
                               + a[4 * col + 2] * b[4 * 2 + row]
                               + a[4 * col + 3] * b[4 * 3 + row];
}

static inline void mat4_mult_vec4(vec4 out, const mat4 a, const vec4 b)
{
    for (int r = 0; r < 4; ++r)
        out[r] = a[r * 4 + 0] * b[0]
               + a[r * 4 + 1] * b[1]
               + a[r * 4 + 2] * b[2]
               + a[r * 4 + 3] * b[3];
}

// Constructions


static inline void mat4_set_identity(mat4 a)
{
    const mat4 IDENTITY_MATRIX = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
    };
    mat4_set(a, IDENTITY_MATRIX);
}

static inline void mat4_set_translate(mat4 a, float x, float y, float z)
{
    const mat4 translation = {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1,
    };
    mat4_set(a, translation);
}

static inline void mat4_set_rotate(mat4 out, float yaw_angle, float pitch_angle)
{
    /*
    // copied from wikipedia
    mat4 orientation = {
        cos_yaw * cos_pitch, cos_yaw * sin_pitch * sin_roll - sin_yaw * cos_roll, cos_yaw * sin_pitch * cos_roll + sin_yaw * sin_roll, 0,
        sin_yaw * cos_pitch, sin_yaw * sin_pitch * sin_roll + cos_yaw * cos_roll, sin_yaw * sin_pitch * cos_roll - cos_yaw * sin_roll, 0,
        -sin_pitch, cos_pitch * sin_roll, cos_pitch * cos_roll, 0,
        0, 0, 0, 1
    };
    */

    float cos_yaw = cosf(yaw_angle);
    float sin_yaw = sinf(yaw_angle);
    float cos_pitch = cosf(pitch_angle);
    float sin_pitch = sinf(pitch_angle);

    mat3 yaw_rotation = {
        cos_yaw, -sin_yaw, 0,
        sin_yaw, cos_yaw, 0,
        0, 0, 1,
    };

    mat3 pitch_rotation = {
        1, 0, 0,
        0, cos_pitch, sin_pitch,
        0, -sin_pitch, cos_pitch,
    };

    mat3 orientation;
    mat3_mult(orientation, pitch_rotation, yaw_rotation);
    mat3_to_mat4(out, orientation);
}

static inline void mat4_set_perspective(mat4 a, float near, float far)
{
    mat4 perspective = {
        1, 0,  0, 0,
        0, 1,  0, 0,
        0, 0, .1, .3,
        0, 0,  0, 1,
    };

    mat4_set(a, perspective);
}

// Print

static inline void mat4_print(mat4 in)
{
    for (int r = 0; r < 16; r+=4)
        printf("%2.2f, %2.2f, %2.2f, %2.2f\n", in[r], in[r + 1], in[r + 2], in[r + 3]);
}

static inline void vec4_print(vec4 in)
{
    printf("%2.2f, %2.2f, %2.2f, %2.2f\n", in[0], in[1], in[2], in[3]);
}

static inline void vec3_print(vec3 in)
{
    printf("%2.2f, %2.2f, %2.2f\n", in[0], in[1], in[2]);
}


#endif // VECMATH_H