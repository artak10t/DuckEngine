#include "Transform.h"

Transform::Transform() {
	parent = nullptr;
	position = glm::vec3(0, 0, 0);
	rotation = 0;
	scale = glm::vec3(1, 1, 1);
	localPosition = glm::vec3(0, 0, 0);
	localRotation = 0;
	localScale = glm::vec3(1, 1, 1);
}

Transform::Transform(glm::vec3 position, float rotation, glm::vec3 scale) {
	parent = nullptr;
	this->position = position;
	this->rotation = rotation;
	this->scale = scale;
	localPosition = glm::vec3(0, 0, 0);
	localRotation = 0;
	localScale = glm::vec3(1, 1, 1);
}

glm::mat4 Transform::Matrix4() {
	glm::mat4 matrix = glm::mat4();
	if (parent)
	{
		glm::mat4 translate4 = glm::translate(glm::mat4(1.0), this->localPosition);
		glm::mat4 rotate4 = glm::rotate(glm::mat4(1.0), glm::radians(this->localRotation), glm::vec3(0, 0, 1));
		glm::mat4 scale4 = glm::scale(glm::mat4(1.0), this->localScale);
		matrix = translate4 * rotate4 * scale4;
		matrix = parent->Matrix4() * matrix;
		position = glm::vec3(matrix[3]);
		rotation = parent->rotation + localRotation;
		scale = localScale;
	}
	else {
		glm::mat4 translate4 = glm::translate(glm::mat4(1.0), this->position);
		glm::mat4 rotate4 = glm::rotate(glm::mat4(1.0), glm::radians(this->rotation), glm::vec3(0, 0, 1));
		glm::mat4 scale4 = glm::scale(glm::mat4(1.0), this->scale);
		matrix = translate4 * rotate4 * scale4;
	}

	return matrix;
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