#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/components/SpriteRenderer.h"

enum class State { Idle, Following };

class Torpedo : public Component
{
public:
	using Component::Component;

	Entity* target;
	State state = State::Idle;
	float maxLifeTime = 5;
	float acceleration = 100;
	float currentVelocity = 0;
	float maxVelocity = 600;
	float rotationVelocity = 3;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("torpedo.png");

		SpriteRenderer* torpedoRenderer = gameObject->AddComponent<SpriteRenderer>();
		torpedoRenderer->sprite = sprite;
		torpedoRenderer->scale = vec2(3, 3);
		torpedoRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

		state = State::Following;
	}

	void Update() {
		currentLifeTime += ofGetLastFrameTime();
		if (target) {
			float relativeVelocity = ofGetLastFrameTime() * currentVelocity;
			float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

			if(currentVelocity < maxVelocity)
				currentVelocity += acceleration * ofGetLastFrameTime();

			if (state == State::Following) {
				gameObject->transform.LookAt(target->transform.position, ofGetLastFrameTime() * rotationVelocity);
				gameObject->transform.position += gameObject->transform.Up() * relativeVelocity;
			}
		}

		if (currentLifeTime >= maxLifeTime) {
			gameObject->Destroy();
		}
	}

private:
	float currentLifeTime = 0;
};