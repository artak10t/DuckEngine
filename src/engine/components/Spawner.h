#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../../game/Torpedo.h"
#include "SpriteRenderer.h"

class Spawner : public Component
{
public:
    using Component::Component;

	Entity* player;
	ofImage torpedoSprite;

	void Start() {
		torpedoSprite.load("torpedo.png");
	}

    void MousePressed(int x, int y, int button) {
        if (button == 0) {
			Entity* torpedo = new Entity();
			torpedo->name = "Torpedo";
			torpedo->transform.position = vec3(x, y, 0);
			Torpedo* torpedoComponent = torpedo->AddComponent<Torpedo>();
			torpedoComponent->player = player;
			torpedoComponent->state = State::Following;
			SpriteRenderer* torpedoRenderer = torpedo->AddComponent<SpriteRenderer>();
			torpedoRenderer->scale = vec2(3, 3);
			torpedoRenderer->sprite = torpedoSprite;
			torpedoRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
        }
    }
};