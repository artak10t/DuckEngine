#include "Controller.h"

void Controller::Update() {
	float relativeVelocity = ofGetLastFrameTime() * velocity;
	float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

	if (forward)
		entity->transform.Position(entity->transform.Position() + entity->transform.Up() * relativeVelocity);
	else if(backward)
		entity->transform.Position(entity->transform.Position() - entity->transform.Up() * relativeVelocity);

	if (rightTurn)
		if(backward)
			entity->transform.Rotation(entity->transform.Rotation() - relativeRotationVelocity);
		else
			entity->transform.Rotation(entity->transform.Rotation() + relativeRotationVelocity);
	else if(leftTurn)
		if(backward)
			entity->transform.Rotation(entity->transform.Rotation() + relativeRotationVelocity);
		else
			entity->transform.Rotation(entity->transform.Rotation() - relativeRotationVelocity);
}

void Controller::KeyPressed(int key) {
	if (key == 'w')
		forward = true;
	else if (key == 's')
		backward = true;

	if (key == 'd')
		rightTurn = true;
	else if (key == 'a')
		leftTurn = true;
}

void Controller::KeyReleased(int key) {
	if (key == 'w')
		forward = false;
	else if (key == 's')
		backward = false;

	if (key == 'd')
		rightTurn = false;
	else if (key == 'a')
		leftTurn = false;
}