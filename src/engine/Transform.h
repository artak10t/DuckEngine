#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	Transform();
	Transform(glm::vec3 position, float rotation, glm::vec3 scale);
	glm::mat4 Matrix4();
	glm::vec3 Up();
	glm::vec3 Right();

	Transform* parent;
	glm::vec3 position;
	float rotation;
	glm::vec3 scale;
	glm::vec3 localPosition;
	float localRotation;
	glm::vec3 localScale;
};

