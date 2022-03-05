#pragma once

#include "../Component.h"
#include "../Entity.h"
#include <app/ofAppRunner.h>

class Controller : public Component
{
public:
	using Component::Component;

	float velocity = 300;
	float rotationVelocity = 100;

	void Update();
	void KeyPressed(int key);
	void KeyReleased(int key);

	vec3 mousePos = vec3(0, 0, 0);
	void MouseMoved(int x, int y) {
		mousePos = vec3(x, y, 0);
	}

private:
	bool forward = false;
	bool backward = false;
	bool leftTurn = false;
	bool rightTurn = false;
};

