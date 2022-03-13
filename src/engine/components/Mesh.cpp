#include "Mesh.h"
bool Mesh::showMeshes = true;

void Mesh::Start() {
	color = ofColor::white;

	//CHANGE, USE POLYLIEN MAYBE
	vertices.push_back(vec3(-24, 24, 0));
	vertices.push_back(vec3(24, 24, 0));
	vertices.push_back(vec3(0, -24, 0));
}

void Mesh::Draw() {
	if (!showMeshes)
		return;

	ofSetColor(color);
	ofFill();
	ofPushMatrix();
	ofMultMatrix(gameObject->transform.Matrix4());
	//CHANGE IN FUTURE
	ofDrawTriangle(vertices[0], vertices[1], vertices[2]);
	ofPopMatrix();
}