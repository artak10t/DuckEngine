#include "Draggable.h"

void Draggable::Start() {
	mesh = gameObject->GetComponent<Mesh>();
}

void Draggable::MouseDragged(int x, int y, int button) {
	if (dragging)
		gameObject->transform.position = vec3(x, y, 0) - delta;
}

void Draggable::MousePressed(int x, int y, int button) {
	if (button == 0) {
		if (inside(vec3(x, y, 0))) {
			dragging = true;
			delta = vec3(x, y, 0) - gameObject->transform.position;
		}
	}

	if (button == 2) {
		if (inside(vec3(x, y, 0))) {
			gameObject->Destroy();
		}
	}
}

void Draggable::MouseReleased(int x, int y, int button) {
	if (button == 0)
		dragging = false;
}

bool Draggable::inside(vec3 point) {
	vec3 p = inverse(gameObject->transform.Matrix4()) * vec4(point, 1);

	vec3 v1 = normalize(mesh->vertices[0] - p);
	vec3 v2 = normalize(mesh->vertices[1] - p);
	vec3 v3 = normalize(mesh->vertices[2] - p);
	float a1 = orientedAngle(v1, v2, vec3(0, 0, 1));
	float a2 = orientedAngle(v2, v3, vec3(0, 0, 1));
	float a3 = orientedAngle(v3, v1, vec3(0, 0, 1));
	if (a1 < 0 && a2 < 0 && a3 < 0) return true;
	else return false;
}