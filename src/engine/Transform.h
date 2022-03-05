#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

class Transform
{
public:
	Transform();
	Transform(vec3 position, float rotation, vec3 scale);
	mat4 Matrix4();
	void LookAt(vec3 target);
	vec3 Up();
	vec3 Right();

	Transform* parent;
	vec3 position;
	float rotation;
	vec3 scale;
	vec3 localPosition;
	float localRotation;
	vec3 localScale;
};

