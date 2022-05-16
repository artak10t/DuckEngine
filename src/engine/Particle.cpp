#include "Particle.h"

void Particle::Update() {
    float dt = ofGetLastFrameTime();
    position += velocity;
    vec3 accel = acceleration;
    accel += forces;
    velocity += accel * dt;
    velocity *= drag;
    forces = vec3(0);

    currentLifeTime += dt;
}