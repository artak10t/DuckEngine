#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/components/Mesh.h"
#include "../engine/components/Rigidbody.h"
#include "../engine/components/BoxCollider.h"

class Lander : public Component
{
public:
    using Component::Component;
    Mesh* mesh;
    Rigidbody* rigidbody;
    BoxCollider* collider;
    ofSoundPlayer thrustSound1;
    ofSoundPlayer thrustSound2;
    float fuel = 10;
    float currentSpeed;

    void Start() {
        // Add sound
        thrustSound1.load("sounds/thrustSound1.wav");
        thrustSound2.load("sounds/thrustSound2.wav");

        // Add mesh
        mesh = gameObject->AddComponent<Mesh>();
        mesh->LoadModel("models/lander.obj");
        mesh->LoadTexture("models/lander.png");

        // Add physics
        rigidbody = gameObject->AddComponent<Rigidbody>();

        // Add collider
        collider = gameObject->AddComponent<BoxCollider>();
        AABB aabb = AABB::MeshBounds(mesh->getMesh());
        collider->Init(aabb.Min(), aabb.Max());
    }

    void Update() {
        currentSpeed = length(rigidbody->velocity);

        if (!up && thrustSound1.isPlaying())
            thrustSound1.stop();

        if (!down && !left && !right && !forward && !backward && !clockwise && !counterClockwise && thrustSound2.isPlaying())
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
    bool up = false;
    bool down = false;
    bool clockwise = false;
    bool counterClockwise = false;
};