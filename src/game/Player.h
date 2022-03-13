#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/components/SpriteRenderer.h"
#include "../engine/components/Collider2D.h"

class Player : public Component
{
public:
    using Component::Component;

	int energy = 5;
    float velocity = 500;
    float rotationVelocity = 300;

	void Start() {
		static ofImage sprite;
		if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
			sprite.load("player.png");

		SpriteRenderer* playerRenderer = gameObject->AddComponent<SpriteRenderer>();
		playerRenderer->sprite = sprite;
		playerRenderer->scale = vec2(2, 2);
		playerRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
		Collider2D* col = gameObject->AddComponent<Collider2D>();

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
			pos += gameObject->transform.Up() * relativeVelocity;
		else if (backward) 
			pos -= gameObject->transform.Up() * relativeVelocity;

		if (pos.x > 0 && pos.x < ofGetWindowWidth() && pos.y > 0 && pos.y < ofGetWindowHeight())
			gameObject->transform.position = pos;

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