#include "Controller.h"

void Controller::Update() {
	float relativeVelocity = ofGetLastFrameTime() * velocity;
	float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

	if (forward)
		entity->transform.position = entity->transform.position + entity->transform.Up() * relativeVelocity;
	else if(backward)
		entity->transform.position = entity->transform.position - entity->transform.Up() * relativeVelocity;

	if (rightTurn)
		if(backward)
			entity->transform.rotation = entity->transform.rotation - relativeRotationVelocity;
		else
			entity->transform.rotation = entity->transform.rotation + relativeRotationVelocity;
	else if(leftTurn)
		if(backward)
			entity->transform.rotation = entity->transform.rotation + relativeRotationVelocity;
		else
			entity->transform.rotation = entity->transform.rotation - relativeRotationVelocity;
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