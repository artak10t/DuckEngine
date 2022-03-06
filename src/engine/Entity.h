#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <typeinfo>
#include "Transform.h"
#include "Component.h"
using namespace std;

class Entity
{
public:
	string name;
	bool isActive;
	Transform transform;

	Entity();
	Entity(string name);
	Entity(string name, vec3 position, float rotation, vec3 scale);
	static void Clear();
	void Destroy();
	void OnDestroy();

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

	static void Update();
	static void Draw();
	static void KeyPressed(int key);
	static void KeyReleased(int key);
	static void MouseMoved(int x, int y);
	static void MouseDragged(int x, int y, int button);
	static void MousePressed(int x, int y, int button);
	static void MouseReleased(int x, int y, int button);
	static void MouseEntered(int x, int y);
	static void MouseExited(int x, int y);
	static void WindowResized(int w, int h);

	~Entity();
private:
	static vector<Entity*> gameObjects;
	static stack<unsigned int> nullPointers;
	void instantiate(Entity* entity);

	unsigned int instanceId;
	vector<Component*> components;
};