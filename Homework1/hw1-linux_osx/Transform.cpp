// Transform.cpp: implementation of the Transform class.

#include "Transform.h"
#include <math.h>

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	mat3 aat = new mat3(
		axis[0]*axis[0], axis[0]*axis[1], axis[0]*axis[2],
		axis[1]*axis[0], axis[1]*axis[1], axis[1]*axis[2],
		axis[2]*axis[0], axis[2]*axis[1], axis[2]*axis[2]
	);
	mat3 astar = new mat3(
		0, -axis[2], axis[1],
		axis[2], 0, -axis[0],
		-axis[1], axis[0], 0
	);
	mat3 identity = new mat3(1);
	// Rodrigues' Rotation Formula
	mat3 rotMat = cosf(degrees)*identity + (1-cosf(degrees))*aat + sinf(degrees)*astar;

	// You will change this return call
	return rotMat();
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	vec3 axis = glm::normalize(up);
	mat3 rotMat = rotate(degrees, axis);
	
	eye = rotMat * eye;
	up = rotMat * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	vec3 forward = glm::normalize(vec3(0, 0, 0) - eye);
	vec3 axis = glm::cross(glm::normalize(up), forward);
	mat3 rotMat = rotate(degrees, axis);
	
	eye = rotMat * eye;
	up = rotMat * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE

	// construct coord frame -> center = (0, 0, 0)
	vec3 campos = new vec3(0, 0, -1);
	vec3 a = eye - campos;
	vec3 b = up;
	vec3 w = a / glm::length(a);
	vec3 u = glm::cross(b, w) / glm::length(glm::cross(b, w));
	vec3 v = glm::cross(w, u);

	// final matrix
	mat4 out = new mat4(
		u.x, u.y, u.z, glm::dot(u, -eye),
		v.x, v.y, v.z, glm::dot(v, -eye),
		w.x, w.y, w.z, glm::dot(w, -eye),
		0, 0, 0, 1
	);

	// You will change this return call
	return out;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
