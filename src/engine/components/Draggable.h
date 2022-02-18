#pragma once

#include "../Component.h"
#include "../Entity.h"
#include <glm/geometric.hpp>
#include <glm/gtx/vector_angle.hpp>

class Draggable : public Component
{
public:
	void MouseDragged(int x, int y, int button);
	void MousePressed(int x, int y, int button);
	void MouseReleased(int x, int y, int button);

private:
	glm::vec3 delta;
	bool dragging = false;

	bool inside(glm::vec3 point);
};

