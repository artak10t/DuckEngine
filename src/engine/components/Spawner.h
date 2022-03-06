#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "Mesh.h"
class Spawner : public Component
{
public:
    using Component::Component;

    void MousePressed(int x, int y, int button) {
        if (button == 0)
        {
            Entity* o = new Entity();
            o->transform.position = vec3(x, y, 0);
            o->AddComponent<Mesh>();
            o->AddComponent<Draggable>();
        }
    }
};