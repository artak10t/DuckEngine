#pragma once
#include <glm/glm.hpp>
using namespace glm;

class AABB
{
public:
	AABB(vec3 min, vec3 max);

	vec3 Max();
	vec3 Min();
	vec3 Center();
	vec3 parameters[2];
};