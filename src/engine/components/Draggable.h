#pragma once

#include "../Component.h"
#include "../Entity.h"
#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Mesh.h"

class Draggable : public Component
{
public:
	using Component::Component;

	void Start();
	void MouseDragged(int x, int y, int button);
	void MousePressed(int x, int y, int button);
	void MouseReleased(int x, int y, int button);

private:
	Mesh* mesh;
	vec3 delta;
	bool dragging = false;
	bool inside(vec3 point);
};

