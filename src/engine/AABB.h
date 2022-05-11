#pragma once
#include <glm/glm.hpp>
using namespace glm;

class AABB
{
public:
	AABB(vec3 min, vec3 max);

	static bool Overlap(AABB collider1, mat4 mat1, AABB collider2, mat4 mat2);

	vec3 Max();
	vec3 Min();
	vec3 Center();
	vec3 parameters[2];
};