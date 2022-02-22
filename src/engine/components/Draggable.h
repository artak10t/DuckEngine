#pragma once

#include "../Component.h"
#include "../Entity.h"
#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "Mesh.h"

class Draggable : public Component
{
public:
	void Start();
	void MouseDragged(int x, int y, int button);
	void MousePressed(int x, int y, int button);
	void MouseReleased(int x, int y, int button);

private:
	Mesh* mesh;
	glm::vec3 delta;
	bool dragging = false;
	bool inside(glm::vec3 point);
};

