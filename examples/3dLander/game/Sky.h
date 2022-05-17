#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/components/Mesh.h"

class Sky : public Component
{
public:
    using Component::Component;
    Mesh* mesh;

    void Start() {
        mesh = gameObject->AddComponent<Mesh>();
        mesh->LoadModel("models/sky.obj");
        mesh->LoadTexture("models/sky.png");
        gameObject->transform.scale = vec3(30);
        gameObject->transform.position = vec3(0, -100, 0);
    }

private:
};