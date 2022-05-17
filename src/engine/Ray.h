#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <3d/ofEasyCam.h>
using namespace glm;

/*
	Class for raycasting purposes.
*/
class Ray
{
public:
	Ray(vec3 origin, vec3 direction);
	Ray(const Ray &ray);

	// Finds the mouse position on the given plane
	static vec3 GetMousePointOnPlane(ofCamera camera, vec3 mousePosition, vec3 planePoint, vec3 planeNorm);

	vec3 origin;
	vec3 direction;
	vec3 invDirection;
	int sign[3];
};