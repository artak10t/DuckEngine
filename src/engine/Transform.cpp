#include "Transform.h"

Transform::Transform() {
	parent = nullptr;
	position = vec3(0, 0, 0);
	rotation = vec3(0, 0, 0);
	scale = vec3(1, 1, 1);
	localPosition = vec3(0, 0, 0);
	localRotation = vec3(0, 0, 0);
	localScale = vec3(1, 1, 1);
}

Transform::Transform(vec3 position, vec3 rotation, vec3 scale) {
	parent = nullptr;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	localPosition = vec3(0, 0, 0);
	localRotation = vec3(0, 0, 0);
	localScale = vec3(1, 1, 1);
}

mat4 Transform::Matrix4() {
	mat4 matrix = mat4();
	if (parent) {
		mat4 translate4 = translate(mat4(1.0), this->localPosition);
		mat4 rotate4 = mat4(1.0);
		rotate4 = rotate(rotate4, radians(this->localRotation.x), vec3(1, 0, 0));
		rotate4 = rotate(rotate4, radians(this->localRotation.y), vec3(0, 1, 0));
		rotate4 = rotate(rotate4, radians(this->localRotation.z), vec3(0, 0, 1));
		mat4 scale4 = glm::scale(mat4(1.0), this->localScale);
		matrix = translate4 * rotate4 * scale4;
		matrix = parent->Matrix4() * matrix;
		position = vec3(matrix[3]);
		rotation = parent->rotation + localRotation;
		scale = localScale;
	}
	else {
		mat4 translate4 = translate(mat4(1.0), this->position);
		mat4 rotate4 = mat4(1.0);
		rotate4 = rotate(rotate4, radians(this->rotation.x), vec3(1, 0, 0));
		rotate4 = rotate(rotate4, radians(this->rotation.y), vec3(0, 1, 0));
		rotate4 = rotate(rotate4, radians(this->rotation.z), vec3(0, 0, 1));
		mat4 scale4 = glm::scale(mat4(1.0), this->scale);
		matrix = translate4 * rotate4 * scale4;
	}

	return matrix;
}

/*
void Transform::LookAt(vec3 target) {
	vec3 relative = target - position;
	float r = ofRadToDeg(atan2(-relative.y, relative.x));
	if (r > 90) {
		r = 450 - r;
	} 
	else {
		r = 90 - r;
	}
	rotation = r;
}
*/

/*
void Transform::LookAt(vec3 target, float deltaTime) {
	vec3 relative = target - position;
	float r = ofRadToDeg(atan2(-relative.y, relative.x));
	if (r > 90) {
		r = 450 - r;
	}
	else {
		r = 90 - r;
	}

	rotation = ofLerpDegrees(rotation, r, deltaTime);
}
*/

vec3 Transform::Up() {
	mat4 rotate4 = mat4(1.0);
	rotate4 = rotate(rotate4, radians(this->rotation.x), vec3(1, 0, 0));
	rotate4 = rotate(rotate4, radians(this->rotation.y), vec3(0, 1, 0));
	rotate4 = rotate(rotate4, radians(this->rotation.z), vec3(0, 0, 1));
	vec3 v = rotate4 * vec4(0, 1, 0, 1);
	return v;
}

vec3 Transform::Right() {
	mat4 rotate4 = mat4(1.0);
	rotate4 = rotate(rotate4, radians(this->rotation.x), vec3(1, 0, 0));
	rotate4 = rotate(rotate4, radians(this->rotation.y), vec3(0, 1, 0));
	rotate4 = rotate(rotate4, radians(this->rotation.z), vec3(0, 0, 1));
	vec3 v = rotate4 * vec4(1, 0, 0, 1);
	return v;
}

vec3 Transform::Forward() {
	mat4 rotate4 = mat4(1.0);
	rotate4 = rotate(rotate4, radians(this->rotation.x), vec3(1, 0, 0));
	rotate4 = rotate(rotate4, radians(this->rotation.y), vec3(0, 1, 0));
	rotate4 = rotate(rotate4, radians(this->rotation.z), vec3(0, 0, 1));
	vec3 v = rotate4 * vec4(0, 0, 1, 1);
	return v;
}