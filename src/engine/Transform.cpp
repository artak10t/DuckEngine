#include "Transform.h"

Transform::Transform() {
	position = glm::vec3(0, 0, 0);
	rotation = 0;
	scale = glm::vec3(1, 1, 1);

	calcMatrix4();
}

Transform::Transform(glm::vec3 position, float rotation, glm::vec3 scale) {
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;

	calcMatrix4();
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

glm::vec3 Transform::Position() {
	return this->position;
}

void Transform::Position(glm::vec3 position) {
	this->position = position;
	calcMatrix4();
}

float Transform::Rotation() {
	return this->rotation;
}

void Transform::Rotation(float rotation) {
	this->rotation = rotation;
	calcMatrix4();
}

glm::vec3 Transform::Scale() {
	return this->scale;
}

void Transform::Scale(glm::vec3 scale) {
	this->scale = scale;
	calcMatrix4();
}

void Transform::calcMatrix4() {
	glm::mat4 translate = glm::translate(glm::mat4(1.0), this->position);
	glm::mat4 rotate = glm::rotate(glm::mat4(1.0), glm::radians(this->rotation), glm::vec3(0, 0, 1));
	glm::mat4 scale = glm::scale(glm::mat4(1.0), this->scale);

	glm::mat4 matrix4 = translate * rotate * scale;
	this->matrix4 = matrix4;
}