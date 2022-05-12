#pragma once
#include <glm/glm.hpp>
#include "ofxAssimpModelLoader.h"
#include "Ray.h"
using namespace glm;

class AABB
{
public:
	AABB() { parameters[0] = vec3(0); parameters[1] = vec3(0); };
	AABB(vec3 min, vec3 max);
	static AABB MeshBounds(ofMesh mesh);

	bool Intersect(AABB aabb);
	bool IntersectRay(Ray ray, float t0, float t1);
	bool Inside(vec3 point);

	vec3 Max();
	vec3 Min();
	vec3 Center();
	vec3 parameters[2];
	vec3 offset = vec3(0);
};