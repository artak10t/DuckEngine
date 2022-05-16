#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/components/Mesh.h"
#include "../engine/components/Rigidbody.h"
#include "../engine/components/BoxCollider.h"
#include "../engine/components/ParticleSystem.h"

class Lander : public Component
{
public:
    using Component::Component;
    bool up = false;
    bool dead = false;
    bool godMode = false;
    Mesh* mesh;
    Mesh* meshDestructed;
    Rigidbody* rigidbody;
    BoxCollider* collider;
    ParticleSystem* thrustParticles;
    ParticleSystem* explosionParticles;
    ofSoundPlayer thrustSound1;
    ofSoundPlayer thrustSound2;
    ofSoundPlayer explosion;
    float fuel = 10;
    float currentSpeed;

    void Explode() {
        if (godMode)
            return;

        fuel = 0;
        dead = true;
        explosionParticles->ShotAll();
        explosion.play();
        rigidbody->freeze = true;
        mesh->visible = false;
        meshDestructed->visible = true;
    }

    void Start() {
        // Add sound
        thrustSound1.load("sounds/thrustSound1.wav");
        thrustSound2.load("sounds/thrustSound2.wav");
        explosion.load("sounds/explosion.wav");

        // Add mesh
        mesh = gameObject->AddComponent<Mesh>();
        mesh->LoadModel("models/lander.obj");
        mesh->LoadTexture("models/lander.png");

        // Add destructed mesh
        meshDestructed = gameObject->AddComponent<Mesh>();
        meshDestructed->LoadModel("models/landerDestructed.obj");
        meshDestructed->LoadTexture("models/lander.png");
        meshDestructed->visible = false;

        // Add physics
        rigidbody = gameObject->AddComponent<Rigidbody>();

        // Add collider
        collider = gameObject->AddComponent<BoxCollider>();
        AABB aabb = AABB::MeshBounds(mesh->getMesh());
        collider->Init(aabb.Min(), aabb.Max());

        // Add Particle System
        thrustParticles = gameObject->AddComponent<ParticleSystem>();
        thrustParticles->InitialScale = 0.5;
        thrustParticles->Enable = false;
        thrustParticles->Shader.load("shaders/shader");
        thrustParticles->Origin = vec3(0, -1, 0);
        thrustParticles->InitialForces = vec3(0, -10, 0);
        thrustParticles->RandomForces = vec3(1, 0, 1);
        thrustParticles->LifeTime = 2;

        explosionParticles = gameObject->AddComponent<ParticleSystem>();
        explosionParticles->InitialScale = 1;
        explosionParticles->Enable = false;
        explosionParticles->Shader.load("shaders/shader");
        explosionParticles->InitialForces = vec3(0, 0, 0);
        explosionParticles->Turbulence = vec3(0, 0.1, 0);
        explosionParticles->RandomForces = vec3(10, 5, 10);
        explosionParticles->Limit = 300;
        explosionParticles->LifeTime = 5;
    }

    void Update() {
        currentSpeed = length(rigidbody->velocity);
        if (godMode)
            fuel = 10;

        if ((!up || fuel <= 0) && thrustParticles->Enable)
            thrustParticles->Enable = false;

        if ((!up || fuel <= 0) && thrustSound1.isPlaying())
            thrustSound1.stop();

        if ((!down && !left && !right && !forward && !backward && !clockwise && !counterClockwise) || fuel <= 0 && thrustSound2.isPlaying())
            thrustSound2.stop();

        if (fuel <= 0)
            return;

        float dt = ofGetLastFrameTime();

        if (left) {
            if (!thrustSound2.isPlaying())
                thrustSound2.play();
            rigidbody->AddForce(gameObject->transform.Right() * 1);
            fuel -= dt;
        }
        else if (right) {
            if (!thrustSound2.isPlaying())
                thrustSound2.play();
            rigidbody->AddForce(-gameObject->transform.Right() * 1);
            fuel -= dt;
        }

        if (forward) {
            if (!thrustSound2.isPlaying())
                thrustSound2.play();
            rigidbody->AddForce(gameObject->transform.Forward() * 1);
            fuel -= dt;
        }
        else if (backward) {
            if (!thrustSound2.isPlaying())
                thrustSound2.play();
            rigidbody->AddForce(-gameObject->transform.Forward() * 1);
            fuel -= dt;
        }

        if (clockwise) {
            if (!thrustSound2.isPlaying())
                thrustSound2.play();
            rigidbody->AddTorque(vec3(0, -1, 0));
            fuel -= dt;
        }
        else if (counterClockwise) {
            if (!thrustSound2.isPlaying())
                thrustSound2.play();
            rigidbody->AddTorque(vec3(0, 1, 0));
            fuel -= dt;
        }

        if (up) {
            if(!thrustSound1.isPlaying())
                thrustSound1.play();
            if (!thrustParticles->Enable)
                thrustParticles->Enable = true;
            rigidbody->AddForce(gameObject->transform.Up() * 1);
            fuel -= dt;
        }
        else if (down) {
            if (!thrustSound2.isPlaying())
                thrustSound2.play();
            rigidbody->AddForce(-gameObject->transform.Up() * 1);
            fuel -= dt;
        }
    }

    void KeyPressed(int key) {
        if (key == 'a')
            left = true;
        else if (key == 'd')
            right = true;

        if (key == 'w')
            forward = true;
        else if (key == 's')
            backward = true;

        if (key == 'e')
            clockwise = true;
        else if (key == 'q')
            counterClockwise = true;

        if (key == 'x')
            up = true;
        else if (key == 'z')
            down = true;
    }

    void KeyReleased(int key) {
        if (key == 'a')
            left = false;
        if (key == 'd')
            right = false;

        if (key == 'w')
            forward = false;
        if (key == 's')
            backward = false;

        if (key == 'e')
            clockwise = false;
        if (key == 'q')
            counterClockwise = false;

        if (key == 'x')
            up = false;
        if (key == 'z')
            down = false;
    }

private:
    bool left = false;
    bool right = false;
    bool forward = false;
    bool backward = false;
    bool down = false;
    bool clockwise = false;
    bool counterClockwise = false;
};