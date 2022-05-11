#pragma once
#include <glm/glm.hpp>
using namespace glm;

class Ray
{
public:
	Ray(vec3 origin, vec3 direction);
	Ray(const Ray &ray);

	vec3 origin;
	vec3 direction;
	vec3 invDirection;
	int sign[3];
};