#pragma once

#include "../Component.h"
#include "../Entity.h"
#include <ofGraphics.h>

class Mesh : public Component
{
public:
	void Start();
	void Draw();

	ofColor color;
	std::vector<glm::vec3> vertices;
};