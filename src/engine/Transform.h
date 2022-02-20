#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform
{
public:
	Transform();
	Transform(glm::vec3 Position, float Rotation, glm::vec3 Scale);

	glm::vec3 Up();
	glm::vec3 Right();

	glm::vec3 Position();
	void Position(glm::vec3 position);
	float Rotation();
	void Rotation(float rotation);
	glm::vec3 Scale();
	void Scale(glm::vec3 scale);

	glm::mat4 matrix4;

private:
	void calcMatrix4();

	glm::vec3 position;
	float rotation;
	glm::vec3 scale;
};

