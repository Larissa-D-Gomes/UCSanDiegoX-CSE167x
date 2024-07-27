// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.
#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
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

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  mat3 rotationMatrix = rotate(degrees, up);
	eye = rotationMatrix * eye; 
	up = rotationMatrix * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
	mat3 rotationMatrix = rotate(degrees, glm::cross(eye, up));
	eye = rotationMatrix * eye; 
	up = rotationMatrix * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
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

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  float degree = fovy * 0.5 * M_PI / 180;
  float d = 1 / tan(degree);

  mat4 m(d/aspect, 0, 0, 0,
         0, d, 0, 0,
         0, 0, -(zFar+zNear)/(zFar - zNear), -2 * zFar * zNear/(zFar - zNear),
         0, 0, -1, 0);
  
  return transpose(m);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  mat4 scaleMatrix = mat4(sx,  0,  0, 0,
                           0, sy,  0, 0,
                           0,  0, sz, 0,
                           0,  0,  0, 1);

  return transpose(scaleMatrix);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  mat4 translationMatrix = mat4(1, 0, 0, tx,
                                0, 1, 0, ty,
                                0, 0, 1, tz,
                                0, 0, 0,  1);

  return transpose(translationMatrix);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}