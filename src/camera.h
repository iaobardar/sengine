#ifndef CAMERA_H
#define CAMERA_H

#include "math.h"

// Type definitions
typedef struct {
    float yaw;
    float pitch;
    float x;
    float y;
    float z;
    float focal_length;
} camera_rig;

// Function declarations
void make_camera_matrix(camera_rig* rig, mat4 camera);
void camera_lookat(vec3 origin, vec3 target, mat4 out);

#endif // CAMERA_H