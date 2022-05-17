#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Physics.h"
#include "../AABB.h"
#include <ofGraphics.h>
#include <gl/ofLight.h>
#include <graphics/of3dGraphics.h>

/*
    BoxCollider component for entites.
    To check if two box collider collider
    gameObject1->boxCollider->aabb.Intersect(gameObject2->boxCollider->aabb)
*/
class BoxCollider : public Component
{
public:
    using Component::Component;

    void Init(vec3 min, vec3 max);
    void Update();
    void Draw();

    bool debugOverlap = false;
    AABB aabb = AABB(vec3(10), vec3(10));

private:
    ofVec3f p;
    float w;
    float h;
    float d;
};

