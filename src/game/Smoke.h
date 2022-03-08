#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "../engine/2d/SpriteRenderer.h"

class Smoke : public Component
{
public:
    using Component::Component;

    float maxLifeTime = 1;

    void Start() {
        static ofImage sprite;
        if (sprite.getWidth() == 0 && sprite.getHeight() == 0)
            sprite.load("smoke.png");

        spriteRenderer = gameObject->AddComponent<SpriteRenderer>();
        spriteRenderer->sprite = sprite;
        spriteRenderer->scale = vec2(3, 3);
        spriteRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
    }

    void Update() {
        currentLifeTime += ofGetLastFrameTime();

        //spriteRenderer->sprite.setColor(spriteRenderer->sprite.getColor())

        if (currentLifeTime >= maxLifeTime)
            gameObject->Destroy();
    }
private:
    SpriteRenderer* spriteRenderer;
    float currentLifeTime = 0;
};