#include "Entity.h"
#include "./components/Draggable.h"

Entity::Entity() {
	transform = Transform();
	name = "New Object";
	isActive = true;
}

void Entity::Start() {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->Start();
}

void Entity::Update() {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->Update();
}

void Entity::Draw() {
	if (!isActive)
		return;

	ofSetColor(mesh.color);
	ofFill();
	ofPushMatrix();
	ofMultMatrix(transform.matrix4);
	//CHANGE IN FUTURE
	ofDrawTriangle(mesh.vertices[0], mesh.vertices[1], mesh.vertices[2]);
	ofPopMatrix();
}

void Entity::KeyPressed(int key) {
	for (int i = 0; i < components.size(); i++)
		components[i]->KeyPressed(key);
}

void Entity::KeyReleased(int key) {
	for (int i = 0; i < components.size(); i++)
		components[i]->KeyReleased(key);
}

void Entity::MouseMoved(int x, int y) {
	for (int i = 0; i < components.size(); i++)
		components[i]->MouseMoved(x, y);
}

void Entity::MouseDragged(int x, int y, int button) {
	for (int i = 0; i < components.size(); i++)
		components[i]->MouseDragged(x, y, button);
}

void Entity::MousePressed(int x, int y, int button) {
	for (int i = 0; i < components.size(); i++)
		components[i]->MousePressed(x, y, button);
}

void Entity::MouseReleased(int x, int y, int button) {
	for (int i = 0; i < components.size(); i++)
		components[i]->MouseReleased(x, y, button);
}

void Entity::MouseEntered(int x, int y) {
	for (int i = 0; i < components.size(); i++)
		components[i]->MouseEntered(x, y);
}

void Entity::MouseExited(int x, int y) {
	for (int i = 0; i < components.size(); i++)
		components[i]->MouseExited(x, y);
}

void Entity::WindowResized(int w, int h) {
	for (int i = 0; i < components.size(); i++)
		components[i]->WindowResized(w, h);
}