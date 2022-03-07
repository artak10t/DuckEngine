#include "Entity.h"
vector<Entity*> Entity::gameObjects = {};
stack<unsigned int> Entity::nullPointers = {};

Entity::Entity() {
	transform = Transform();
	name = "New Object";
	isActive = true;
	instanceId = gameObjects.size();
	instantiate(this);
}

Entity::Entity(string name) {
	transform = Transform();
	this->name = name;
	isActive = true;
	instanceId = gameObjects.size();
	instantiate(this);
}

Entity::Entity(string name, vec3 position, float rotation, vec3 scale) {
	transform = Transform(position, rotation, scale);
	this->name = name;
	isActive = true;
	instanceId = gameObjects.size();
	instantiate(this);
}

void Entity::instantiate(Entity* entity) {
	if (Entity::nullPointers.size() == 0) {
		Entity::gameObjects.push_back(entity);
		return;
	}

	unsigned int p = Entity::nullPointers.top();
	Entity::nullPointers.pop();
	entity->instanceId = p;
	Entity::gameObjects[p] = entity;
}

void Entity::Clear() {
	for (int i = 0; i < Entity::gameObjects.size(); i++) {
		delete Entity::gameObjects[i];
	}

	Entity::gameObjects.clear();
}

void Entity::Destroy() {
	OnDestroy();

	Entity::gameObjects[instanceId] = nullptr;
	nullPointers.push(instanceId);
	delete this;
}

void Entity::OnDestroy() {
	int sizeComponent = components.size();
	for (int j = 0; j < sizeComponent; j++)
		components[j]->OnDestroy();
}

Entity::~Entity() {
	for (int i = 0; i < components.size(); i++)
		delete components[i];

	components.clear();
}

void Entity::Update() {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->Update();
		}
}

void Entity::Draw() {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->Draw();
		}
}

void Entity::KeyPressed(int key) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->KeyPressed(key);
		}
}

void Entity::KeyReleased(int key) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->KeyReleased(key);
		}
}

void Entity::MouseMoved(int x, int y) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->MouseMoved(x, y);
		}
}

void Entity::MouseDragged(int x, int y, int button) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->MouseDragged(x, y, button);
		}
}

void Entity::MousePressed(int x, int y, int button) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->MousePressed(x, y, button);
		}
}

void Entity::MouseReleased(int x, int y, int button) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->MouseReleased(x, y, button);
		}
}

void Entity::MouseEntered(int x, int y) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->MouseEntered(x, y);
		}
}

void Entity::MouseExited(int x, int y) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->MouseExited(x, y);
		}
}

void Entity::WindowResized(int w, int h) {
	int size = Entity::gameObjects.size();
	for (int i = 0; i < size; i++)
		if (Entity::gameObjects[i]) {
			if (!Entity::gameObjects[i]->isActive)
				return;

			int sizeComponent = Entity::gameObjects[i]->components.size();
			for (int j = 0; j < sizeComponent; j++)
				if (Entity::gameObjects[i])
					Entity::gameObjects[i]->components[j]->WindowResized(w, h);
		}
}