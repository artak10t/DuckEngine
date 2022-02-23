#include "Transform.h"

Transform::Transform() {
	position = glm::vec3(0, 0, 0);
	rotation = 0;
	scale = glm::vec3(1, 1, 1);
	matrix4_cached = Matrix4();
}

Transform::Transform(glm::vec3 position, float rotation, glm::vec3 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	matrix4_cached = Matrix4();
}

glm::mat4 Transform::Matrix4() {
	if(last_position == position && last_rotation == rotation && last_scale == scale)
		return matrix4_cached;

	last_position = position;
	last_rotation = rotation;
	last_scale = scale;
	glm::mat4 translate = glm::translate(glm::mat4(1.0), this->position);
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0), glm::radians(this->rotation), glm::vec3(0, 0, 1));
	glm::mat4 scale = glm::scale(glm::mat4(1.0), this->scale);

	matrix4_cached = translate * rotate * scale;
	return matrix4_cached;
}

glm::vec3 Transform::Up() {
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0), glm::radians(this->rotation), glm::vec3(0, 0, 1));
	glm::vec3 v = rotate * glm::vec4(0, -1, 0, 1);
	return v;
}

glm::vec3 Transform::Right() {
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0), glm::radians(this->rotation), glm::vec3(0, 0, 1));
	glm::vec3 v = rotate * glm::vec4(1, 0, 0, 1);
	return v;
}