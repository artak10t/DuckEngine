#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Physics.h"
#include <app/ofAppRunner.h>

class Rigidbody : public Component
{
public:
    using Component::Component;
    float drag = 0.99;
    float angularDrag = 0.99;
    float mass = 1;
    float momentOfInertia = 1;
    vec3 gravityForce = vec3(0, 9.8, 0);
    vec3 velocity = vec3(0, 0, 0);
    vec3 angularVelocity = vec3(0, 0, 0);
    vec3 acceleration = vec3(0, 0, 0);
    vec3 angularAcceleration = vec3(0, 0, 0);

    void Update();
    void AddForce(vec3 force);
    void AddTorque(vec3 torque);

private:
    vec3 forces = vec3(0, 0, 0);
    vec3 torques = vec3(0, 0, 0);
};