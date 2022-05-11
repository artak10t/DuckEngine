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

    void Start() {
        // Show axis
        gameObject->transform.debugAxis = DebugAxis::Local;

        // Add mesh
        mesh = gameObject->AddComponent<Mesh>();
        mesh->LoadModel("models/lander.obj");
        mesh->LoadTexture("models/moon.png");

        // Add physics
        rigidbody = gameObject->AddComponent<Rigidbody>();
        rigidbody->gravityForce = vec3(0, 0, 0);

        // Add collider
        collider = gameObject->AddComponent<BoxCollider>();
        collider->Init(vec3(-5), vec3(5));
    }

    void Update() {
        if (left)
            rigidbody->AddForce(-gameObject->transform.Right() * 1);
        else if (right)
            rigidbody->AddForce(gameObject->transform.Right() * 1);

        if (forward)
            rigidbody->AddForce(gameObject->transform.Forward() * 1);
        else if (backward)
            rigidbody->AddForce(-gameObject->transform.Forward() * 1);

        if (clockwise)
            rigidbody->AddTorque(vec3(0, 1, 0));
        else if (counterClockwise)
            rigidbody->AddTorque(vec3(0, -1, 0));

        if (up)
            rigidbody->AddForce(gameObject->transform.Up() * 1);
        else if (down)
            rigidbody->AddForce(-gameObject->transform.Up() * 1);
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

        if (key == OF_KEY_LEFT_SHIFT)
            up = true;
        else if (key == OF_KEY_LEFT_CONTROL)
            down = true;
    }

    void KeyReleased(int key) {
        if (key == 'a')
            left = false;
        else if (key == 'd')
            right = false;

        if (key == 'w')
            forward = false;
        else if (key == 's')
            backward = false;

        if (key == 'e')
            clockwise = false;
        else if (key == 'q')
            counterClockwise = false;

        if (key == OF_KEY_LEFT_SHIFT)
            up = false;
        else if (key == OF_KEY_LEFT_CONTROL)
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