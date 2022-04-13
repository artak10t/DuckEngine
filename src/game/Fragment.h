#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/components/Rigidbody2D.h"
#include "../engine/components/SpriteRenderer.h"
#include <app/ofAppRunner.h>

class Fragment : public Component
{
public:
	using Component::Component;
	float maxLifeTime = 1;
	float strength = 1;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("explosion.png");

		SpriteRenderer* renderer = gameObject->AddComponent<SpriteRenderer>();
		renderer->sprite = sprite;
		renderer->scale = vec2(4, 4);
		renderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		color = &renderer->color;
		rotation = ofRandomf() * 180;
		gameObject->transform.rotation = rotation;
		Rigidbody2D* rigidbody2D = gameObject->AddComponent<Rigidbody2D>();
		float strRand = ofRandomf() + 1.5;
		strength = strRand;
		strength *= 200;
		rigidbody2D->gravityForce = vec3(0, 0, 0);
		rigidbody2D->AddForce(gameObject->transform.Up() * strength);
		rotation = ofRandomf();
	}

	void Update() {
		gameObject->transform.rotation += rotation;
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