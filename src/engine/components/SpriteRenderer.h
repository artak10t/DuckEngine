#include <graphics/ofImage.h>
#include <graphics/ofGraphics.h>
#include "../Component.h"
#include "../Entity.h"

class SpriteRenderer : public Component
{
public:
    using Component::Component;

    ofImage sprite;
    vec2 scale = vec2(1, 1);

    void Update() {
        scaledWidth = sprite.getWidth() * scale.x;
        scaledHeight = sprite.getHeight() * scale.y;
    }

    void Draw() {
        ofPushMatrix();
        ofMultMatrix(gameObject->transform.Matrix4());
        sprite.draw(-scaledWidth / 2, -scaledHeight / 2, scaledWidth, scaledHeight);
        ofPopMatrix();
    }
private:
    float scaledWidth = 0;
    float scaledHeight = 0;
};