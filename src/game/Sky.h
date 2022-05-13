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
        gameObject->transform.scale = vec3(2);
        gameObject->transform.position = vec3(0, -200, 0);
        gameObject->transform.rotation = vec3(90, 0, 0);
    }

private:
};