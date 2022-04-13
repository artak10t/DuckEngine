#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../game/Smoke.h"
#include "../game/Bullet.h"
#include "../engine/components/SpriteRenderer.h"
#include "../engine/components/Collider2D.h"
#include "../engine/components/Rigidbody2D.h"

class Player : public Component
{
public:
    using Component::Component;

	int energy = 5;
    float velocity = 500;
    float rotationVelocity = 300;
	float bounciness = 1;
	float sliping = 20;
	float fireRate = 0.1;
	Rigidbody2D* rigidbody2D;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("player.png");

		SpriteRenderer* playerRenderer = gameObject->AddComponent<SpriteRenderer>();
		playerRenderer->sprite = sprite;
		playerRenderer->scale = vec2(2, 2);
		playerRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		Collider2D* col = gameObject->AddComponent<Collider2D>();
		rigidbody2D = gameObject->AddComponent<Rigidbody2D>();
		rigidbody2D->gravityForce = vec3(0, 0, 0);
		rigidbody2D->drag = 0.99;

		col->vertices.clear();
		col->vertices.push_back(vec2(-45, -30));
		col->vertices.push_back(vec2(-24, 28));
		col->vertices.push_back(vec2(24, 28));
		col->vertices.push_back(vec2(45, -30));
	}

    void Update() {
		float relativeVelocity = ofGetLastFrameTime() * velocity;
		float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

		vec3 pos = gameObject->transform.position;
		if (forward)
		{
			rigidbody2D->AddForce(gameObject->transform.Up() * relativeVelocity);
			smokeEffect();
		}
		else if (backward)
		{
			rigidbody2D->AddForce(-gameObject->transform.Up() * relativeVelocity);
			smokeEffect();
		}

		if (pos.x < 0)
		{
			gameObject->transform.position = vec3(0, gameObject->transform.position.y, gameObject->transform.position.z);
			rigidbody2D->velocity = vec3(-rigidbody2D->velocity.x * bounciness, rigidbody2D->velocity.y, rigidbody2D->velocity.z);
		}
		if (pos.x > ofGetWindowWidth())
		{
			gameObject->transform.position = vec3(ofGetWindowWidth(), gameObject->transform.position.y, gameObject->transform.position.z);
			rigidbody2D->velocity = vec3(-rigidbody2D->velocity.x * bounciness, rigidbody2D->velocity.y, rigidbody2D->velocity.z);
		}
		if (pos.y < 0)
		{
			gameObject->transform.position = vec3(gameObject->transform.position.x, 0, gameObject->transform.position.z);
			rigidbody2D->velocity = vec3(rigidbody2D->velocity.x, -rigidbody2D->velocity.y * bounciness, rigidbody2D->velocity.z);
		}
		if (pos.y > ofGetWindowHeight())
		{
			gameObject->transform.position = vec3(gameObject->transform.position.x, ofGetWindowHeight(), gameObject->transform.position.z);
			rigidbody2D->velocity = vec3(rigidbody2D->velocity.x, -rigidbody2D->velocity.y * bounciness, rigidbody2D->velocity.z);
		}

		if (rightTurn)
			if (backward)
				gameObject->transform.rotation -= relativeRotationVelocity;
			else
				gameObject->transform.rotation += relativeRotationVelocity;
		else if (leftTurn)
			if (backward)
				gameObject->transform.rotation += relativeRotationVelocity;
			else
				gameObject->transform.rotation -= relativeRotationVelocity;

		vec3 rightVelocity = length(rigidbody2D->velocity) * gameObject->transform.Up();
		vec3 delta = (rightVelocity - rigidbody2D->velocity) / sliping;
		rigidbody2D->velocity = rigidbody2D->velocity + delta;

		if (shooting)
			shoot();

		if (fireTime > 0)
			fireTime -= ofGetLastFrameTime();

		currentSmokeSpawnTime -= ofGetLastFrameTime() * length(rigidbody2D->velocity) * 2;
    }

    void KeyPressed(int key) {
		if (key == 'w')
			forward = true;
		else if (key == 's')
			backward = true;

		if (key == 'd')
			rightTurn = true;
		else if (key == 'a')
			leftTurn = true;

		if (key == ' ')
			shooting = true;
    }

    void KeyReleased(int key) {
		if (key == 'w')
			forward = false;
		else if (key == 's')
			backward = false;

		if (key == 'd')
			rightTurn = false;
		else if (key == 'a')
			leftTurn = false;

		if (key == ' ')
			shooting = false;
    }

private:
    bool forward = false;
    bool backward = false;
    bool leftTurn = false;
    bool rightTurn = false;
	bool shooting = false;
	float smokeTime = 1;
	float currentSmokeSpawnTime;
	float fireTime = 0;

	void shoot()
	{
		if (fireTime > 0)
			return;

		Entity* bullet = new Entity("Bullet");
		bullet->transform.position = gameObject->transform.position + gameObject->transform.Up() * 35;
		bullet->transform.rotation = gameObject->transform.rotation;
		Bullet* b = bullet->AddComponent<Bullet>();
		fireTime = fireRate;
	}

	void smokeEffect()
	{
		if (currentSmokeSpawnTime > 0)
			return;

		Entity* smoke = new Entity("Smoke");
		smoke->transform.position = gameObject->transform.position + -gameObject->transform.Up() * 25;
		smoke->AddComponent<Smoke>();
		currentSmokeSpawnTime = smokeTime;
	}
};