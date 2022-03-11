#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/components/SpriteRenderer.h"
#include "../engine/components/Collider2D.h"
#include "Smoke.h"
#include "Explosion.h"

enum class State { Idle, Following };

class Torpedo : public Component
{
public:
	using Component::Component;

	Entity** target;
	Collider2D* targetCollider;
	State state = State::Idle;
	float maxLifeTime = 8;
	float acceleration = 100;
	float currentVelocity = 0;
	float maxVelocity = 600;
	float rotationVelocity = 3;

	float smokeSpawnTime = 30;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("torpedo.png");

		SpriteRenderer* torpedoRenderer = gameObject->AddComponent<SpriteRenderer>();
		torpedoRenderer->sprite = sprite;
		torpedoRenderer->scale = vec2(2, 2);
		torpedoRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

		selfCollider = gameObject->AddComponent<Collider2D>();
		selfCollider->vertices.clear();
		selfCollider->vertices.push_back(vec2(-8, -24));
		selfCollider->vertices.push_back(vec2(-8, 24));
		selfCollider->vertices.push_back(vec2(8, 24));
		selfCollider->vertices.push_back(vec2(8, -24));

		state = State::Following;
	}

	void Update() {
		//Seeking
		if (*target) {
			//Collision and explosion
			selfCollider->overlap = Collider2D::CollisionCheck(*selfCollider, *targetCollider);
			if (selfCollider->overlap) {
				Player* p = (*target)->GetComponent<Player>();
				p->energy--;
				Entity* explosion = new Entity("Explosion");
				explosion->transform.position = gameObject->transform.position;
				explosion->AddComponent<Explosion>();
				gameObject->Destroy();
				return;
			}

			float relativeVelocity = ofGetLastFrameTime() * currentVelocity;
			float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

			if(currentVelocity < maxVelocity)
				currentVelocity += acceleration * ofGetLastFrameTime();

			if (state == State::Following) {
				gameObject->transform.LookAt((*target)->transform.position, ofGetLastFrameTime() * rotationVelocity);
				gameObject->transform.position += gameObject->transform.Up() * relativeVelocity;
			}
		}

		//Smoke
		if (currentSmokeSpawnTime >= smokeSpawnTime) {
			Entity* smoke = new Entity("Smoke");
			smoke->transform.position = gameObject->transform.position + -gameObject->transform.Up() * 15;
			smoke->AddComponent<Smoke>();
			currentSmokeSpawnTime = 0;
		}

		if (currentLifeTime >= maxLifeTime) {
			gameObject->Destroy();
			return;
		}

		currentLifeTime += ofGetLastFrameTime();
		currentSmokeSpawnTime += ofGetLastFrameTime() * currentVelocity;
	}

private:
	Collider2D* selfCollider;
	float currentLifeTime = 0;
	float currentSmokeSpawnTime = 0;
};