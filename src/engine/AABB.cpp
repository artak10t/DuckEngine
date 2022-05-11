#include "AABB.h"

AABB::AABB(vec3 min, vec3 max) {
	parameters[0] = min;
	parameters[1] = max;
}

bool AABB::Overlap(AABB collider1, mat4 mat1, AABB collider2, mat4 mat2) {
	AABB col1 = collider1;
	col1.parameters[0] = mat1 * vec4(col1.parameters[0], 1);
	col1.parameters[1] = mat1 * vec4(col1.parameters[1], 1);

	AABB col2 = collider2;
	col2.parameters[0] = mat2 * vec4(col2.parameters[0], 1);
	col2.parameters[1] = mat2 * vec4(col2.parameters[1], 1);

	int i = 0;
	if (col1.parameters[0].x <= col2.parameters[1].x && col1.parameters[1].x >= col2.parameters[0].x)
		i++;
	if (col1.parameters[0].y <= col2.parameters[1].y && col1.parameters[1].y >= col2.parameters[0].y)
		i++;
	if (col1.parameters[0].z <= col2.parameters[1].z && col1.parameters[1].z >= col2.parameters[0].z)
		i++;
	if (i == 3)
		return true;

	return false;
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