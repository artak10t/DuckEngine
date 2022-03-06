#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
enum class State { Idle, Rotating, Following };

class Torpedo : public Component
{
public:
	using Component::Component;

	Entity* player;
	State state = State::Idle;
	float acceleration = 100;
	float velocity = 0;
	float maxVelocity = 600;
	float rotationVelocity = 3;

	void Update() {
		if (player) {
			float relativeVelocity = ofGetLastFrameTime() * velocity;
			float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

			if(velocity < maxVelocity)
				velocity += acceleration * ofGetLastFrameTime();

			if (state == State::Rotating)
				gameObject->transform.LookAt(player->transform.position, ofGetLastFrameTime() * rotationVelocity);

			if (state == State::Following) {
				gameObject->transform.LookAt(player->transform.position, ofGetLastFrameTime() * rotationVelocity);
				gameObject->transform.position += gameObject->transform.Up() * relativeVelocity;
			}
		}
	}
};