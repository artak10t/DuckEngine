#include "Rigidbody.h"

void Rigidbody::Update() {
    if (!Physics::enablePhysics)
        return;

    if (mass == 0)
        mass = 0.001;
    if (momentOfInertia == 0)
        momentOfInertia = 0.001;

    float dt = ofGetLastFrameTime();
    gameObject->transform.position += velocity;
    gameObject->transform.rotation += angularVelocity;

    vec3 accel = acceleration;
    vec3 anglAccel = angularAcceleration;
    accel += (forces * (1 / mass));
    anglAccel += (torques * (1 / momentOfInertia));

    velocity += accel * dt;
    angularVelocity += anglAccel * dt;
    velocity *= drag;
    angularVelocity *= angularDrag;

    forces = gravityForce;
    torques = vec3(0, 0, 0);
}

void Rigidbody::AddForce(vec3 force) {
    forces += force;
}

void Rigidbody::AddTorque(vec3 torque) {
    torques += torque;
}