#pragma once

#include <ofGraphics.h>
#include <typeinfo>
#include "Transform.h"
#include "Component.h"

class Entity
{
public:
	Entity();
	void Destroy();

	template<typename T> T* AddComponent() {
		T* component = new T(this);
		for (int i = 0; i < components.size(); i++) {
			if (typeid(*components[i]) == typeid(*component))
				return nullptr;
		}

		components.push_back(component);
		components[components.size() - 1]->Start();
		return dynamic_cast<T*>(component);
	}

	template<typename T> T* GetComponent() {
		for (int i = 0; i < components.size(); i++) {
			if (typeid(*components[i]) == typeid(T))
				return dynamic_cast<T*>(components[i]);
		}

		return nullptr;
	}

	template<typename T> void RemoveComponent() {
		for (int i = 0; i < components.size(); i++) {
			if (typeid(*components[i]) == typeid(T)) {
				delete components[i];
				components.erase(components.begin() + i);
			}
		}
	}

	void Update();
	void Draw();
	void OnDestroy();
	void KeyPressed(int key);
	void KeyReleased(int key);
	void MouseMoved(int x, int y);
	void MouseDragged(int x, int y, int button);
	void MousePressed(int x, int y, int button);
	void MouseReleased(int x, int y, int button);
	void MouseEntered(int x, int y);
	void MouseExited(int x, int y);
	void WindowResized(int w, int h);

	std::string name;
	bool isActive;
	Transform transform;

	static std::vector<Entity*> gameObjects;

	~Entity();
private:
	unsigned int instanceId;
	std::vector<Component*> components;
};