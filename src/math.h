#ifndef MATH_H
#define MATH_H

// Type definitions
typedef float mat4[4 * 4];
typedef float vec4[4];
typedef float vec3[3];

// Vec3 operations
void vec3add(vec3 a, vec3 b, vec3 out);
void vec3sub(vec3 a, vec3 b, vec3 out);
void vec3scale(vec3 a, float s, vec3 out);
void vec3addip(vec3 a, vec3 b);
void vec3subip(vec3 a, vec3 b);
void vec3scaleip(vec3 a, float s);
float vec3dot(vec3 a, vec3 b);
float vec3length(vec3 a);
void vec3normip(vec3 a);
void vec3cross(vec3 a, vec3 b, vec3 out);

// Mat4 operations
void mat4copy(const mat4 origin, mat4 target);
void mat4mult(mat4 a, mat4 b, mat4 out);
void mat4transform(mat4 transformation, mat4 target);

// Print functions
void mat4print(mat4 in);
void vec4print(vec4 in);

// Vec4 operations
float vec4dot(vec4 a, vec4 b);
void mat4multvec3(mat4 a, vec4 b, vec4 out);

// Mat4 constructions
void mat4make_identity(mat4 a);
void mat4make_translate(mat4 a, float x, float y, float z);
void mat4make_rotate(mat4 a, float yaw, float pitch);
void mat4make_perspective(mat4 a, float near, float far);

#endif // MATH_H