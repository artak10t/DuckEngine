#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/components/Mesh.h"
#include "../engine/components/TerrainCollider.h"

class Moon : public Component
{
public:
    using Component::Component;
    Mesh* mesh;
    TerrainCollider* collider;

    void Start() {
        mesh = gameObject->AddComponent<Mesh>();
        mesh->LoadModel("models/moon.obj");
        mesh->LoadTexture("models/moon.png");
        mesh->Material.setShininess(0.01);
        collider = gameObject->AddComponent<TerrainCollider>();
        collider->Init(levels);
    }

private:
    int levels = 20;
};