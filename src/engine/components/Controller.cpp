#include "Controller.h"
#include "../components/Mesh.h"
#include "../components/Controller.h"

void Controller::Update() {
	float relativeVelocity = ofGetLastFrameTime() * velocity;
	float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

	if (forward)
		gameObject->transform.position = gameObject->transform.position + gameObject->transform.Up() * relativeVelocity;
	else if(backward)
		gameObject->transform.position = gameObject->transform.position - gameObject->transform.Up() * relativeVelocity;

	if (rightTurn)
		if(backward)
			gameObject->transform.rotation = gameObject->transform.rotation - relativeRotationVelocity;
		else
			gameObject->transform.rotation = gameObject->transform.rotation + relativeRotationVelocity;
	else if(leftTurn)
		if(backward)
			gameObject->transform.rotation = gameObject->transform.rotation + relativeRotationVelocity;
		else
			gameObject->transform.rotation = gameObject->transform.rotation - relativeRotationVelocity;
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

	if (key == 'k')
		gameObject->Destroy();

	if (key == 'f') {
		Entity* o = new Entity();
		o->name = "B";
		o->transform.position = gameObject->transform.position;
		o->AddComponent<Mesh>();
		o->AddComponent<Controller>();
	}
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