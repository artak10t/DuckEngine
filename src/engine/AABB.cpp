#include "AABB.h"

AABB::AABB(vec3 min, vec3 max) {
	parameters[0] = min;
	parameters[1] = max;
}

vec3 AABB::Max() {
	return parameters[1];
}

vec3 AABB::Min() {
	return parameters[0];
}

vec3 AABB::Center() {
	vec3 a = Max() - Min();
	a /= 2;
	a += Min();

	return a;
}