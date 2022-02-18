#include "Draggable.h"

void Draggable::MouseDragged(int x, int y, int button) {
	if (dragging)
		entity->transform.Position(glm::vec3(x, y, 0) - delta);
}

void Draggable::MousePressed(int x, int y, int button) {
	if (button == 0) {
		if (inside(glm::vec3(x, y, 0))) {
			dragging = true;
			delta = glm::vec3(x, y, 0) - entity->transform.Position();
		}
	}
}

void Draggable::MouseReleased(int x, int y, int button) {
	if (button == 0)
		dragging = false;
}

bool Draggable::inside(glm::vec3 point) {
	glm::vec3 p = glm::inverse(entity->transform.matrix4) * glm::vec4(point, 1);

	glm::vec3 v1 = glm::normalize(entity->mesh.vertices[0] - p);
	glm::vec3 v2 = glm::normalize(entity->mesh.vertices[1] - p);
	glm::vec3 v3 = glm::normalize(entity->mesh.vertices[2] - p);
	float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
	float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
	float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));
	if (a1 < 0 && a2 < 0 && a3 < 0) return true;
	else return false;
}