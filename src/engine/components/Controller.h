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

private:
	bool forward = false;
	bool backward = false;
	bool leftTurn = false;
	bool rightTurn = false;
};

