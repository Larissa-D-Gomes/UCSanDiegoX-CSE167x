// Transform.cpp: implementation of the Transform class.


#include "Transform.h"

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	vec3 normA = normalize(axis);

	float rad = degrees * pi / 180.0;
	float sinT = sin(rad);
	float cosT = cos(rad);
	float oneMinCos = 1 - cosT;

	glm::mat3 rotationMatrix = glm::mat3(
		cosT + (oneMinCos) * normA.x * normA.x,
		(oneMinCos) * normA.y * normA.x + sinT * normA.z,
		(oneMinCos) * normA.z * normA.x - sinT * normA.y,
		(oneMinCos) * normA.x * normA.y - sinT * normA.z,
		cosT + (oneMinCos) * normA.y * normA.y,
		(oneMinCos) * normA.z * normA.y + sinT * normA.x,
		(oneMinCos) * normA.x * normA.z + sinT * normA.y,
		(oneMinCos) * normA.y * normA.z - sinT * normA.x,
		cosT + (oneMinCos) * normA.z * normA.z
	);

	return rotationMatrix;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	mat3 rotationMatrix = rotate(degrees, up);
	eye = rotationMatrix * eye; 
	up = rotationMatrix * up;
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	mat3 rotationMatrix = rotate(degrees, glm::cross(eye, up));
	eye = rotationMatrix * eye; 
	up = rotationMatrix * up;
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
    vec3 w = glm::normalize(eye);
	vec3 u = glm::normalize(glm::cross(up, w));
	vec3 v = glm::cross(w, u);

	mat4 lAMatrix = mat4(
		u.x, v.x, w.x, 0, 
		u.y, v.y, w.y, 0, 
		u.z, v.z, w.z, 0, 
		-glm::dot(u, eye), -glm::dot(v, eye), -glm::dot(w, eye), 1);

	return lAMatrix;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
