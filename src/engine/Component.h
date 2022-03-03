#pragma once

class Entity;

class Component
{
public:
	Component(Entity* gameObject) { this->gameObject = gameObject; }
	virtual void Start() {}
	virtual void Update() {}
	virtual void Draw() {}
	virtual void OnDestroy() {}
	virtual void KeyPressed(int key) {}
	virtual void KeyReleased(int key) {}
	virtual void MouseMoved(int x, int y) {}
	virtual void MouseDragged(int x, int y, int button) {}
	virtual void MousePressed(int x, int y, int button) {}
	virtual void MouseReleased(int x, int y, int button) {}
	virtual void MouseEntered(int x, int y) {}
	virtual void MouseExited(int x, int y) {}
	virtual void WindowResized(int w, int h) {}
	Entity* gameObject;

	virtual ~Component() {}
protected:
};