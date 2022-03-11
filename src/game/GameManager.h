#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "Player.h"
#include "Torpedo.h"

class GameManager
{
public:
    float totalGameTime = 0;
    float spawnRate = 3;
    float lifeSpan = 10;
    float torpedoAcceleration = 100;
    Entity* player;

    void Start() {
        if (gameStarted)
            return;

        totalGameTime = 0;
        spawnRate = 3;
        lifeSpan = 10;
        torpedoAcceleration = 100;

        gameStarted = true;
        Entity::Clear();
        player = new Entity("Player");
        player->transform.position = vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
        playerComponent = player->AddComponent<Player>();
    }

    void Update() {
        if (gameStarted) {
            totalGameTime += ofGetLastFrameTime();
            currentSpawnTime += ofGetLastFrameTime();

            if (totalGameTime > 120) {
                spawnRate = 0.5;
                torpedoAcceleration = 500;
            }
            else if (totalGameTime > 60) {
                spawnRate = 0.75;
                torpedoAcceleration = 400;
            }
            else if (totalGameTime > 30) {
                spawnRate = 1;
                torpedoAcceleration = 300;
            }
            else if (totalGameTime > 10) {
                spawnRate = 2;
                torpedoAcceleration = 200;
            }

            if (currentSpawnTime >= spawnRate) {
                currentSpawnTime = 0;

                vec3 pos = vec3(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()), 0);
                Entity* torpedo = new Entity("Torpedo");
                torpedo->transform.position = pos;
                Torpedo* component = torpedo->AddComponent<Torpedo>();
                component->target = &player;
                component->targetCollider = player->GetComponent<Collider2D>();
            }

            if (playerComponent->energy <= 0)
                End();
        }
    }

    void End() {
        Entity* boom = new Entity("Player");
        boom->transform.position = player->transform.position;
        Explosion* explosion = boom->AddComponent<Explosion>();
        explosion->strength = 3;

        player->Destroy();
        gameStarted = false;
        player = nullptr;
        playerComponent = nullptr;
        totalGameTime = 0;
    }

private:
    Player* playerComponent;

    bool gameStarted;
    float currentSpawnTime = 0;
};