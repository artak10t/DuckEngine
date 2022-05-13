#include "Rigidbody2D.h"

void Rigidbody2D::Update() {
    if (!Physics::enablePhysics || ofGetLastFrameTime() > 1)
        return;

    if (mass == 0)
        mass = 0.001;

    float dt = ofGetLastFrameTime();
    gameObject->transform.position += velocity;
    vec3 accel = acceleration;
    accel += (forces * (1 / mass));
    velocity += accel * dt;
    velocity *= drag;
    forces = vec3(0, 0, 0);
    AddForce(Physics::gravity);
}

void Rigidbody2D::AddForce(vec3 force) {
    forces += force;
}