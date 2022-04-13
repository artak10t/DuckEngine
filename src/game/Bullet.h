#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/components/Mesh.h"
#include "../engine/components/Rigidbody2D.h"
#include "../engine/components/SpriteRenderer.h"
#include <app/ofAppRunner.h>

class Bullet : public Component
{
public:
	using Component::Component;
	float maxLifeTime = 2;
	float velocity = 1000;
	int i = 0;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("bullet.png");

		SpriteRenderer* renderer = gameObject->AddComponent<SpriteRenderer>();
		renderer->sprite = sprite;
		renderer->scale = vec2(4, 4);
		renderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		color = &renderer->color;
		gameObject->AddComponent<Mesh>();
		Rigidbody2D* rigidbody2D = gameObject->AddComponent<Rigidbody2D>();
		rigidbody2D->gravityForce = vec3(0, 0, 0);
		rigidbody2D->drag = 1;
		rigidbody2D->AddForce(gameObject->transform.Up() * velocity);
	}

	void Update() {
		color->a = 255 - ofNormalize(currentLifeTime, 0, maxLifeTime) * 255;

		if (currentLifeTime >= maxLifeTime) {
			gameObject->Destroy();
			return;
		}

		currentLifeTime += ofGetLastFrameTime();
	}

private:
	float rotation = 0;
	float currentLifeTime = 0;
	ofColor* color;
};