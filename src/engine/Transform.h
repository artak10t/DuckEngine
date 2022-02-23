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

	glm::vec3 position;
	float rotation;
	glm::vec3 scale;

private:
	glm::mat4 matrix4_cached;
	glm::vec3 last_position;
	float last_rotation;
	glm::vec3 last_scale;
};

