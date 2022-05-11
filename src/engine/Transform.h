#pragma once
#include <iostream>
#include <math/ofMath.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
using namespace glm;

enum class DebugAxis { None, Local, Global };

class Transform
{
public:
	Transform();
	Transform(vec3 position, vec3 rotation, vec3 scale);
	mat4 Matrix4();
	//void LookAt(vec3 target);
	//void LookAt(vec3 target, float deltaTime);
	vec3 Up();
	vec3 Right();
	vec3 Forward();

	Transform* parent;
	vec3 position;
	vec3 rotation;
	vec3 scale;
	vec3 localPosition;
	vec3 localRotation;
	vec3 localScale;

	DebugAxis debugAxis = DebugAxis::None;
};

