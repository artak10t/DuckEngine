#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Physics.h"
#include <ofGraphics.h>
#include <ofPoint.h>
#include <graphics/ofPolyline.h>

class Collider2D : public Component
{
public:
    using Component::Component;

    static bool CollisionCheck(Collider2D& poly1, Collider2D& poly2);

    std::vector<vec2> vertices;
    bool overlap = false;
    bool debug = true;

    void Start();
    void Update();
    void Draw();
private:
    ofPolyline colliderVisual;
    std::vector<vec2> verticesWorldSpace;
};

