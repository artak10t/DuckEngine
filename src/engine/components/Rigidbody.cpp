#include "Rigidbody.h"

void Rigidbody::Update() {
    if (mass == 0)
        mass = 0.001;

    float dt = ofGetLastFrameTime();
    gameObject->transform.position += velocity * dt;
    velocity += force * (1 / mass + Physics::gravity) * dt;
    velocity *= drag;
}