#pragma once
#include "../Component.h"
#include "../Entity.h"
#include <graphics/ofImage.h>
#include <graphics/ofGraphics.h>

class SpriteRenderer : public Component
{
public:
    using Component::Component;

    ofImage sprite;
    ofColor color = ofColor::white;
    vec2 scale = vec2(1, 1);

    void Update();
    void Draw();
private:
    float scaledWidth = 0;
    float scaledHeight = 0;
};