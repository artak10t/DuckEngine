#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include <app/ofAppRunner.h>
#include "../engine/components/SpriteRenderer.h"

class Player : public Component
{
public:
    using Component::Component;

    float velocity = 500;
    float rotationVelocity = 300;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("player.png");

		SpriteRenderer* playerRenderer = gameObject->AddComponent<SpriteRenderer>();
		playerRenderer->sprite = sprite;
		playerRenderer->scale = vec2(3, 3);
		playerRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	}

    void Update() {
		float relativeVelocity = ofGetLastFrameTime() * velocity;
		float relativeRotationVelocity = ofGetLastFrameTime() * rotationVelocity;

		if (forward)
			gameObject->transform.position += gameObject->transform.Up() * relativeVelocity;
		else if (backward)
			gameObject->transform.position -= gameObject->transform.Up() * relativeVelocity;

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
    }

private:
    bool forward = false;
    bool backward = false;
    bool leftTurn = false;
    bool rightTurn = false;
};