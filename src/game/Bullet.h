#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/components/Mesh.h"
#include "../engine/components/Rigidbody2D.h"
#include "../engine/components/SpriteRenderer.h"
#include "../engine/components/Collider2D.h"
#include <app/ofAppRunner.h>
#include "Torpedo.h"
#include "Player.h"

class Bullet : public Component
{
public:
	using Component::Component;
	float maxLifeTime = 2;
	float velocity = 1000;
	vector<Collider2D*>* torpedos = {};
	Player* p;
	int maxEnergy = 5;
	int i = 0;
	ofSoundPlayer laserAudio;

	void Start() {
		static ofImage sprite;
		static ofSoundPlayer sound;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("bullet.png");
		if (!sound.isLoaded())
			sound.load("laser.wav");
		laserAudio = sound;

		SpriteRenderer* renderer = gameObject->AddComponent<SpriteRenderer>();
		renderer->sprite = sprite;
		renderer->scale = vec2(4, 4);
		renderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		color = &renderer->color;
		gameObject->AddComponent<Mesh>();
		selfCollider = gameObject->AddComponent<Collider2D>();
		selfCollider->vertices.clear();
		selfCollider->vertices.push_back(vec2(-8, -20));
		selfCollider->vertices.push_back(vec2(-8, 20));
		selfCollider->vertices.push_back(vec2(8, 20));
		selfCollider->vertices.push_back(vec2(8, -20));
		Rigidbody2D* rigidbody2D = gameObject->AddComponent<Rigidbody2D>();
		rigidbody2D->gravityForce = vec3(0, 0, 0);
		rigidbody2D->drag = 1;
		rigidbody2D->AddForce(gameObject->transform.Up() * velocity);
		laserAudio.play();
	}

	void Update() {
		color->a = 255 - ofNormalize(currentLifeTime, 0, maxLifeTime) * 255;
		int j = torpedos->size();
		for (int i = 0; i < j; i++)
		{
			if (i >= torpedos->size())
				break;

			selfCollider->overlap = Collider2D::CollisionCheck(*selfCollider, *(*torpedos)[i]);
			if (selfCollider->overlap)
			{
				Torpedo* t = (*torpedos)[i]->gameObject->GetComponent<Torpedo>();
				t->destroy = true;
				if (p && p->energy < maxEnergy)
					p->energy++;
				break;
			}
		}

		if (currentLifeTime >= maxLifeTime) {
			gameObject->Destroy();
			return;
		}

		currentLifeTime += ofGetLastFrameTime();
	}

private:
	Collider2D* selfCollider;
	float rotation = 0;
	float currentLifeTime = 0;
	ofColor* color;
};