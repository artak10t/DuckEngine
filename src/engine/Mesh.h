#pragma once

#include <ofGraphics.h>

class Mesh
{
public:
	Mesh();

	ofColor color;
	std::vector<glm::vec3> vertices;
};