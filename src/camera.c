
typedef struct {
	float yaw; float pitch;
	float x; float y; float z;
	float focal_length;
} camera_rig;

void make_camera_matrix(camera_rig* rig, mat4 camera)
{
	mat4 translate, rotate, perspective, temp;

	mat4make_translate(translate, -rig->x, -rig->y, -rig->z);
	mat4make_rotate(rotate, -rig->yaw, -rig->pitch);
	mat4make_perspective(perspective, 0, 1);

	mat4mult(translate, rotate, camera);
	//mat4mult(temp, perspective, camera);
}

void camera_lookat(vec3 origin, vec3 target, mat4 out)
{
	vec3 world_up = {0, 0, 1};

	vec3 up, side, forward;

	vec3sub(target, origin, forward);
	vec3normip(forward);

	vec3cross(forward, world_up, side);
	vec3normip(side);

	vec3cross(side, forward, up);

	mat4 camera = {

	};
	mat4copy(camera, out);
}