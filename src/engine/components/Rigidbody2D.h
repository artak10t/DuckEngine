#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Physics.h"
#include <app/ofAppRunner.h>

class Rigidbody2D : public Component
{
public:
    using Component::Component;
    float drag = 0.99;
    float mass = 1;
    vec3 velocity = vec3(0, 0, 0);
    vec3 acceleration = vec3(0, 0, 0);

    void Update();
    void AddForce(vec3 force);

private:
    vec3 forces = vec3(0, 0, 0);
};