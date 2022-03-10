#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Physics.h"
#include <app/ofAppRunner.h>

class Rigidbody : public Component
{
public:
    using Component::Component;
    float drag = 0.8;
    float mass = 1;
    vec3 velocity = vec3(0, 0, 0);
    vec3 force = vec3(0, 0, 0);

    void Update();
};