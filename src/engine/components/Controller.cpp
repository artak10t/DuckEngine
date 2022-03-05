#include "Controller.h"
#include "../components/Mesh.h"
#include "../components/Controller.h"

void Controller::Update() {
	gameObject->transform.LookAt(mousePos);
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

Transform* cached;
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

	if (key == 'c' && gameObject->name == "b" && gameObject->transform.parent) {
		cached = gameObject->transform.parent;
		gameObject->transform.parent = NULL;
	}
	else if (key == 'c' && gameObject->name == "b" && !gameObject->transform.parent) {
		gameObject->transform.parent = cached;
	}

	if (key == 'h')
		gameObject->transform.localPosition += vec3(10, 0, 0);

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