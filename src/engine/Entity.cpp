#include "Entity.h"
std::vector<Entity*> Entity::gameObjects = {};

Entity::Entity() {
	transform = Transform();
	name = "New Object";
	isActive = true;
	instanceId = gameObjects.size();
	Entity::gameObjects.push_back(this);
}

Entity::~Entity() {
	for (int i = 0; i < components.size(); i++)
		delete components[i];

	components.clear();
}

void Entity::Destroy() {
	OnDestroy();

	Entity::gameObjects[instanceId] = nullptr;
	delete this;
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

	for (int i = 0; i < components.size(); i++)
		components[i]->Draw();
}

void Entity::OnDestroy() {
	for (int i = 0; i < components.size(); i++)
		components[i]->OnDestroy();
}

void Entity::KeyPressed(int key) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->KeyPressed(key);
}

void Entity::KeyReleased(int key) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->KeyReleased(key);
}

void Entity::MouseMoved(int x, int y) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->MouseMoved(x, y);
}

void Entity::MouseDragged(int x, int y, int button) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->MouseDragged(x, y, button);
}

void Entity::MousePressed(int x, int y, int button) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->MousePressed(x, y, button);
}

void Entity::MouseReleased(int x, int y, int button) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->MouseReleased(x, y, button);
}

void Entity::MouseEntered(int x, int y) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->MouseEntered(x, y);
}

void Entity::MouseExited(int x, int y) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->MouseExited(x, y);
}

void Entity::WindowResized(int w, int h) {
	if (!isActive)
		return;

	for (int i = 0; i < components.size(); i++)
		components[i]->WindowResized(w, h);
}