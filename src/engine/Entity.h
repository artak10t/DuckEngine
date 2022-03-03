#pragma once

#include <ofGraphics.h>
#include <typeinfo>
#include "Transform.h"
#include "Component.h"

class Entity
{
public:
	Entity();

	static void Instantiate(Entity* gameObject) {
		gameObjects.push_back(gameObject);
	}

	static void Destroy(Entity* gameObject) {

	}

	template<typename T> T* AddComponent() {
		T* component = new T(this);
		for (int i = 0; i < components.size(); i++) {
			if (typeid(*components[i]) == typeid(*component))
				return nullptr;
		}

		components.push_back(component);
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

	void RemoveAllComponents() {
		for (int i = 0; i < components.size(); i++)
			delete components[i];
	}

	virtual void Start();
	virtual void Update();
	virtual void Draw();
	virtual void KeyPressed(int key);
	virtual void KeyReleased(int key);
	virtual void MouseMoved(int x, int y);
	virtual void MouseDragged(int x, int y, int button);
	virtual void MousePressed(int x, int y, int button);
	virtual void MouseReleased(int x, int y, int button);
	virtual void MouseEntered(int x, int y);
	virtual void MouseExited(int x, int y);
	virtual void WindowResized(int w, int h);

	std::string name;
	bool isActive;
	Transform transform;

	static std::vector<Entity*> gameObjects;
private:
	std::vector<Component*> components;
};