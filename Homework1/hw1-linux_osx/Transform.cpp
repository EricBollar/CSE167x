// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <math.h>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE

	// You will change this return call
	return mat3();
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	vec3 axis = glm::normalize(up);
	mat3 aat = mat3(
		axis[0]*axis[0], axis[0]*axis[1], axis[0]*axis[2],
		axis[1]*axis[0], axis[1]*axis[1], axis[1]*axis[2],
		axis[2]*axis[0], axis[2]*axis[1], axis[2]*axis[2]
	);
	mat3 astar = mat3(
		0, -axis[2], axis[1],
		axis[2], 0, -axis[0],
		-axis[1], axis[0], 0
	);
	mat3 identity = mat3(1);
	// Rodrigues' Rotation Formula
	mat3 rotMat = cosf(degrees)*identity + (1-cosf(degrees))*aat + sinf(degrees)*astar;
	eye = rotMat * eye;
	up = rotMat * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	vec3 forward = glm::normalize(vec3(0, 0, 0) - eye);
	vec3 axis = glm::cross(glm::normalize(up), forward);
	mat3 aat = mat3(
		axis[0]*axis[0], axis[0]*axis[1], axis[0]*axis[2],
		axis[1]*axis[0], axis[1]*axis[1], axis[1]*axis[2],
		axis[2]*axis[0], axis[2]*axis[1], axis[2]*axis[2]
	);
	mat3 astar = mat3(
		0, -axis[2], axis[1],
		axis[2], 0, -axis[0],
		-axis[1], axis[0], 0
	);
	mat3 identity = mat3(1);
	// Rodrigues' Rotation Formula
	mat3 rotMat = cosf(degrees)*identity + (1-cosf(degrees))*aat + sinf(degrees)*astar;
	eye = rotMat * eye;
	up = rotMat * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE

	// You will change this return call
	return mat4();
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
