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
	Rigidbody2D* rigidbody2D;
	State state = State::Idle;
	float maxLifeTime = 8;
	float velocity = 10;
	float rotationVelocity = 3;
	float sliping = 20;
	Collider2D* selfCollider;
	bool destroy = false;

	float smokeSpawnTime = 1;
	float launch = 2;
	int i = 0;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("torpedo.png");

		SpriteRenderer* torpedoRenderer = gameObject->AddComponent<SpriteRenderer>();
		torpedoRenderer->sprite = sprite;
		torpedoRenderer->scale = vec2(2, 2);
		torpedoRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

		rigidbody2D = gameObject->AddComponent<Rigidbody2D>();
		rigidbody2D->gravityForce = vec3(0, 0, 0);
	}

	void Update() {
		//Seeking
		if (*target) {
			//Collision and explosion
			selfCollider->overlap = Collider2D::CollisionCheck(*selfCollider, *targetCollider);
			if (selfCollider->overlap) {
				Player* p = (*target)->GetComponent<Player>();
				p->energy--;
				destroy = true;
				return;
			}

			float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;
			gameObject->transform.LookAt((*target)->transform.position, ofGetLastFrameTime() * rotationVelocity);
			if (launch <= 0 && state != State::Following)
				state = State::Following;

			if (state == State::Following) {
				vec3 rightVelocity = length(rigidbody2D->velocity) * gameObject->transform.Up();
				vec3 delta = (rightVelocity - rigidbody2D->velocity) / sliping;
				rigidbody2D->velocity = rigidbody2D->velocity + delta;
				rigidbody2D->AddForce(gameObject->transform.Up() * velocity);
			}
		}

		//Smoke
		if (currentSmokeSpawnTime >= smokeSpawnTime) {
			Entity* smoke = new Entity("Smoke");
			smoke->transform.position = gameObject->transform.position + -gameObject->transform.Up() * 15;
			smoke->AddComponent<Smoke>();
			currentSmokeSpawnTime = 0;
		}

		if (launch > 0)
			launch -= ofGetLastFrameTime();

		if (currentLifeTime >= maxLifeTime || destroy) {
			destroy = true;
			return;
		}

		currentLifeTime += ofGetLastFrameTime();
		currentSmokeSpawnTime += ofGetLastFrameTime() * length(rigidbody2D->velocity) * 2;
	}

private:
	float currentLifeTime = 0;
	float currentSmokeSpawnTime = 0;
};