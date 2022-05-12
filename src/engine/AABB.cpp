#include "AABB.h"

AABB::AABB(vec3 min, vec3 max) {
	parameters[0] = min;
	parameters[1] = max;
}

/*
	We translate points by position offset and
	check if two boxes are inside each other.
*/
bool AABB::Intersect(AABB aabb) {
	AABB col1 = aabb;
	col1.parameters[0] += col1.offset;
	col1.parameters[1] += col1.offset;

	AABB col2 = *this;
	col2.parameters[0] += col2.offset;
	col2.parameters[1] += col2.offset;

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

/*
	We translate AABB box by position offset and
	check if ray intersects.
*/
bool AABB::IntersectRay(Ray ray, float t0, float t1) {
	float tmin, tmax, tymin, tymax, tzmin, tzmax;
	AABB col = *this;
	col.parameters[0] += col.offset;
	col.parameters[1] += col.offset;

	tmin = (col.parameters[ray.sign[0]].x - ray.origin.x) * ray.invDirection.x;
	tmax = (col.parameters[1 - ray.sign[0]].x - ray.origin.x) * ray.invDirection.x;
	tymin = (col.parameters[ray.sign[1]].y - ray.origin.y) * ray.invDirection.y;
	tymax = (col.parameters[1 - ray.sign[1]].y - ray.origin.y) * ray.invDirection.y;
	if ((tmin > tymax) || (tymin > tmax))
		return false;
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (col.parameters[ray.sign[2]].z - ray.origin.z) * ray.invDirection.z;
	tzmax = (col.parameters[1 - ray.sign[2]].z - ray.origin.z) * ray.invDirection.z;
	if ((tmin > tzmax) || (tzmin > tmax))
		return false;
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return ((tmin < t1) && (tmax > t0));
}

/*
	Finds if given points is inside the AABB.
*/
bool AABB::Inside(vec3 point) {
	AABB col = *this;
	col.parameters[0] += col.offset;
	col.parameters[1] += col.offset;

	return ((point.x >= col.parameters[0].x && point.x <= col.parameters[1].x) &&
			(point.y >= col.parameters[0].y && point.y <= col.parameters[1].y) &&
			(point.z >= col.parameters[0].z && point.z <= col.parameters[1].z));
}

/*
	Creates AABB box for the given mesh.
*/
AABB AABB::MeshBounds(ofMesh mesh) {
	int n = mesh.getNumVertices();
	ofVec3f v = mesh.getVertex(0);
	ofVec3f max = v;
	ofVec3f min = v;
	for (int i = 1; i < n; i++) {
		ofVec3f v = mesh.getVertex(i);

		if (v.x > max.x) max.x = v.x;
		else if (v.x < min.x) min.x = v.x;

		if (v.y > max.y) max.y = v.y;
		else if (v.y < min.y) min.y = v.y;

		if (v.z > max.z) max.z = v.z;
		else if (v.z < min.z) min.z = v.z;
	}
	
	return AABB(vec3(min.x, min.y, min.z), vec3(max.x, max.y, max.z));
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