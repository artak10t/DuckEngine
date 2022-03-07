#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../../game/Torpedo.h"
#include "SpriteRenderer.h"

class Spawner : public Component
{
public:
    using Component::Component;

    Entity* player;

    void MousePressed(int x, int y, int button) {
        if (button == 0) {
			Entity* torpedo = new Entity();
			torpedo->name = "Torpedo";
			torpedo->transform.position = vec3(x, y, 0);
			torpedo->AddComponent<Torpedo>()->target = player;
        }
    }
};