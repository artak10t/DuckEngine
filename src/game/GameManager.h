#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "ofxGui.h"
#include "Player.h"
#include "Torpedo.h"
#include "../engine/components/Mesh.h"

class GameManager
{
public:
    float totalGameTime = 0;
    float spawnRate = 3;
    int agentNumbers = 1;
    float lifeSpan = 8;
    float torpedoAcceleration = 100;
    bool debug = false;
    Entity* player;

    void Setup() {
        gui.setup();
        gui.add(energyGui.setup("Player Energy", 5, 0, 10));
        gui.add(playerSpeedGui.setup("Player Speed", 500, 1, 1000));
        gui.add(playerScaleGui.setup("Player Scale", 1, 0.1, 5));
        gui.add(spawnRateGui.setup("Agent Spawn Rate", 2, 0.5, 10));
        gui.add(agentNumbersGui.setup("Agent Spawn Number", 1, 1, 5));
        gui.add(agentLifespanGui.setup("Agent Life Span", 8, 0, 10));
        gui.add(showCollidersGui.setup("Show Colliders", false));
        gui.add(showSpritesGui.setup("Show Sprites", true));
        gui.add(godModeGui.setup("God mode", false));
    }

    void Start() {
        if (gameStarted)
            return;

        totalGameTime = 0;
        energyGui = 5;
        torpedoAcceleration = 100;

        gameStarted = true;
        Entity::Clear();
        player = new Entity("Player");
        player->transform.position = vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
        playerComponent = player->AddComponent<Player>();
        energyGui.addListener(this, &GameManager::ListenerEnergy);
        maxEnergy = playerComponent->energy;
        player->AddComponent<Mesh>();
    }

    void ListenerEnergy(int& value) {
        playerComponent->energy = value;
        maxEnergy = value;
    }

    void Update() {
        spawnRate = spawnRateGui;
        agentNumbers = agentNumbersGui;
        lifeSpan = agentLifespanGui;
        Physics::showColliders = showCollidersGui;
        Mesh::showMeshes = !showSpritesGui;
        SpriteRenderer::showSprites = showSpritesGui;

        if (gameStarted) {
            player->transform.scale = vec3(playerScaleGui);
            playerComponent->velocity = playerSpeedGui;

            totalGameTime += ofGetLastFrameTime();
            currentSpawnTime += ofGetLastFrameTime();

            if (totalGameTime > 120) {
                torpedoAcceleration = 500;
            }
            else if (totalGameTime > 60) {
                torpedoAcceleration = 400;
            }
            else if (totalGameTime > 30) {
                torpedoAcceleration = 300;
            }
            else if (totalGameTime > 10) {
                torpedoAcceleration = 200;
            }

            if (currentSpawnTime >= spawnRate) {
                currentSpawnTime = 0;

                for (int i = 0; i < agentNumbers; i++) {
                    vec3 pos = vec3(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()), 0);
                    Entity* torpedo = new Entity("Torpedo");
                    torpedo->transform.position = pos;
                    torpedo->transform.rotation = ofRandom(360);
                    Torpedo* component = torpedo->AddComponent<Torpedo>();
                    component->maxLifeTime = lifeSpan;
                    component->target = &player;
                    component->targetCollider = player->GetComponent<Collider2D>();
                    torpedo->AddComponent<Mesh>();
                }
            }

            if (playerComponent->energy <= 0 && !godModeGui)
                End();
        }
    }

    void Draw() {
        ofSetColor(ofColor::green);
        if (!gameStarted)
            ofDrawBitmapString("Press Space to Start", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2);
        else if(gameStarted && player) {
            ofDrawBitmapString("Total time " + to_string(totalGameTime), ofGetWindowWidth() / 2, 30);
            ofDrawBitmapString("Energy level " + to_string(playerComponent->energy) + "|" + to_string(maxEnergy), ofGetWindowWidth() / 2 - 150, 30);
            ofDrawBitmapString("Frame rate " + to_string(ofGetFrameRate()), ofGetWindowWidth() - 200, 30);
        }

        if (debug)
            gui.draw();
    }

    void End() {
        Entity* boom = new Entity("Player");
        boom->transform.position = player->transform.position;
        Explosion* explosion = boom->AddComponent<Explosion>();
        explosion->strength = 3;

        player->Destroy();
        energyGui.removeListener(this, &GameManager::ListenerEnergy);
        gameStarted = false;
        player = nullptr;
        playerComponent = nullptr;
        totalGameTime = 0;
    }

private:
    Player* playerComponent;

    int maxEnergy;
    bool gameStarted;
    float currentSpawnTime = 0;

    ofxPanel gui;
    ofxIntSlider energyGui;
    ofxFloatSlider playerScaleGui;
    ofxFloatSlider playerSpeedGui;
    ofxFloatSlider spawnRateGui;
    ofxIntSlider agentNumbersGui;
    ofxFloatSlider agentLifespanGui;
    ofxToggle showCollidersGui = false;
    ofxToggle godModeGui = false;
    ofxToggle showSpritesGui = true;
};