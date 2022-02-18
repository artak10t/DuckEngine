#include "Mesh.h"

Mesh::Mesh() {
	color = ofColor::white;

	//CHANGE, USE POLYLIEN MAYBE
	vertices.push_back(glm::vec3(-50, 50, 0));
	vertices.push_back(glm::vec3(50, 50, 0));
	vertices.push_back(glm::vec3(0, -50, 0));
}