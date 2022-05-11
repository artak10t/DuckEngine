#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Physics.h"
#include "../AABB.h"
#include <ofGraphics.h>
#include <gl/ofLight.h>
#include <graphics/of3dGraphics.h>

class BoxCollider : public Component
{
public:
    using Component::Component;

    void Init(vec3 min, vec3 max);
    void Start();
    void Update();
    void Draw();
private:
    AABB aabb = AABB(vec3(10), vec3(10));
    ofVec3f p;
    float w;
    float h;
    float d;
};

