#pragma once
#include "../Component.h"
#include "../Entity.h"
#include <ofGraphics.h>

class Mesh : public Component
{
public:
	using Component::Component;

	void Start();
	void Draw();
	void MakeSmall() {
		vertices.clear();
		vertices.push_back(vec3(-25, 25, 0));
		vertices.push_back(vec3(25, 25, 0));
		vertices.push_back(vec3(0, -25, 0));
	}

	ofColor color;
	std::vector<vec3> vertices;
};