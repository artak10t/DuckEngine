#include "Ray.h"

Ray::Ray(vec3 origin, vec3 direction) {
    this->origin = origin;
    this->direction = direction;
    invDirection = vec3(1 / direction.x, 1 / direction.y, 1 / direction.z);
    sign[0] = (invDirection.x < 0);
    sign[1] = (invDirection.y < 0);
    sign[2] = (invDirection.z < 0);
}

Ray::Ray(const Ray& ray) {
    origin = ray.origin;
    direction = ray.direction;
    invDirection = ray.invDirection;
    sign[0] = ray.sign[0]; sign[1] = ray.sign[1]; sign[2] = ray.sign[2];
}

vec3 Ray::GetMousePointOnPlane(ofCamera camera, vec3 mousePosition, vec3 planePoint, vec3 planeNorm) {
	glm::vec3 origin = camera.getPosition();
	glm::vec3 camAxis = camera.getZAxis();
	glm::vec3 mouseWorld = camera.screenToWorld(mousePosition);
	glm::vec3 mouseDir = glm::normalize(mouseWorld - origin);
	float distance;

	bool hit = intersectRayPlane(origin, mouseDir, planePoint, planeNorm, distance);

	if (hit) {
		vec3 intersectPoint = origin + distance * mouseDir;

		return intersectPoint;
	}
	else return glm::vec3(0, 0, 0);
}