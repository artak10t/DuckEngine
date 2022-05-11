#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/components/BoxCollider.h"

class LandingZone : public Component
{
public:
    using Component::Component;
    BoxCollider* collider;

    void Start() {
        collider = gameObject->AddComponent<BoxCollider>();
        collider->Init(vec3(0, 0, 0), vec3(20, 2, 20));
    }

    bool CheckSpeed(float speed) {
        if (speed <= 0.01)
            return true;

        return false;
    }

private:
};