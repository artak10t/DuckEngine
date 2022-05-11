#pragma once
#include <glm/glm.hpp>
#include "Ray.h"
using namespace glm;

class AABB
{
public:
	AABB(vec3 min, vec3 max);

	bool Overlap(AABB aabb);
	bool RayOverlap(Ray ray, float t0, float t1);

	vec3 Max();
	vec3 Min();
	vec3 Center();
	vec3 parameters[2];
	vec3 offset;
};