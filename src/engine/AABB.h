#pragma once
#include <glm/glm.hpp>
#include "ofxAssimpModelLoader.h"
#include "Ray.h"
using namespace glm;

/*
	Axis Aligned Bounding Box class.
	Used ray and other AABB collision detection.
*/
class AABB
{
public:
	AABB() { parameters[0] = vec3(0); parameters[1] = vec3(0); };
	AABB(vec3 min, vec3 max);

	// Creates and return AABB based on the given mesh
	static AABB MeshBounds(ofMesh mesh);

	// Collision with other AABB
	bool Intersect(AABB aabb);

	// Collision with ray
	bool IntersectRay(Ray ray, float t0, float t1);

	// Check if point is inside the AABB
	bool Inside(vec3 point);

	vec3 Max();
	vec3 Min();
	vec3 Center();
	vec3 parameters[2];
	vec3 offset = vec3(0);
};