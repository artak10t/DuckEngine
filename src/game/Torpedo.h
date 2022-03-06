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
	float velocity = 100;
	float rotationVelocity = 100;

	void Update() {
		if (player) {
			float relativeVelocity = ofGetLastFrameTime() * velocity;
			float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

			if (state == State::Rotating)
				gameObject->transform.LookAt(player->transform.position);

			if (state == State::Following) {
				gameObject->transform.LookAt(player->transform.position);
				gameObject->transform.position += gameObject->transform.Up() * relativeVelocity;
			}
		}
	}
};