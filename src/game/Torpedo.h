#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/2d/SpriteRenderer.h"
#include "../engine/2d/Collider2D.h"

enum class State { Idle, Following };

class Torpedo : public Component
{
public:
	using Component::Component;

	Entity* target;
	Collider2D* targetCollider;
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

		selfCollider = gameObject->AddComponent<Collider2D>();

		SpriteRenderer* torpedoRenderer = gameObject->AddComponent<SpriteRenderer>();
		torpedoRenderer->sprite = sprite;
		torpedoRenderer->scale = vec2(3, 3);
		torpedoRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

		state = State::Following;
	}

	void Update() {
		selfCollider->overlap = Collider2D::CollisionCheck(*selfCollider, *targetCollider);

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
	Collider2D* selfCollider;
	float currentLifeTime = 0;
};