#include "Mesh.h"

void Mesh::Start() {
	color = ofColor::white;

	//CHANGE, USE POLYLIEN MAYBE
	vertices.push_back(vec3(-50, 50, 0));
	vertices.push_back(vec3(50, 50, 0));
	vertices.push_back(vec3(0, -50, 0));
}

void Mesh::Draw() {
	ofSetColor(color);
	ofFill();
	ofPushMatrix();
	ofMultMatrix(gameObject->transform.Matrix4());
	//CHANGE IN FUTURE
	ofDrawTriangle(vertices[0], vertices[1], vertices[2]);
	ofPopMatrix();
}