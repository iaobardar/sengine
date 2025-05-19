#ifndef CAMERA_H
#define CAMERA_H

#include "vecmath.h"

typedef struct {
    float yaw;
    float pitch;
    float x;
    float y;
    float z;

    float fov; // vertical field of view
    float aspect_ratio; // width / height
    float near;
} camera_t;

void camera_matrix(camera_t* camera, mat4 camera_matrix);
void camera_lookat(vec3 origin, vec3 target, float fov, mat4 out);

#endif // CAMERA_H