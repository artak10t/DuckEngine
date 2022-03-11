#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/components/SpriteRenderer.h"
#include <app/ofAppRunner.h>

class Smoke : public Component
{
public:
	using Component::Component;
	float maxLifeTime = 1;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("smoke.png");

		SpriteRenderer* renderer = gameObject->AddComponent<SpriteRenderer>();
		renderer->sprite = sprite;
		renderer->scale = vec2(2, 2);
		renderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		color = &renderer->color;
		rotation = ofRandomf();
	}

	void Update() {
		gameObject->transform.rotation += rotation;
		gameObject->transform.scale += vec3(0.03, 0.03, 0.03);
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