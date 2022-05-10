#pragma once
#include "../engine/Component.h"
#include "../engine/Entity.h"
#include "ofxGui.h"
#include "Player.h"
#include "Torpedo.h"
#include "Bullet.h"

class GameManager
{
public:
    float totalGameTime = 0;
    float spawnRate = 3;
    int agentNumbers = 1;
    int difficulty = 1;
    float lifeSpan = 5;
    float torpedoAcceleration = 100;
    bool debug = false;
    bool shooting = false;
    float fireTime = 0;
    float fireRate = 0.1;
    Entity* player;
    vector<Collider2D*> torpedos;
    vector<Torpedo*> torp;

    GameManager()
    {
        startLevelAudio.load("start-level.wav");
        endLevelAudio.load("end-level.wav");
    }

    void Setup() {
        gui.setup();
        gui.add(energyGui.setup("Player Energy", 5, 0, 10));
        gui.add(playerSpeedGui.setup("Player Speed", 500, 1, 1000));
        gui.add(fireRateGui.setup("Fire Rate", 0.1, 0.01, 1));
        gui.add(playerScaleGui.setup("Player Scale", 1, 0.1, 5));
        gui.add(spawnRateGui.setup("Agent Spawn Rate", 2, 0.5, 10));
        gui.add(agentNumbersGui.setup("Agent Spawn Number", 1, 1, 5));
        gui.add(agentLifespanGui.setup("Agent Life Span", 5, 0, 10));
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
        startLevelAudio.play();

        gameStarted = true;
        Entity::Clear();
        player = new Entity("Player");
        player->transform.position = vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
        playerComponent = player->AddComponent<Player>();
        energyGui.addListener(this, &GameManager::ListenerEnergy);
        maxEnergy = playerComponent->energy;
    }

    void ListenerEnergy(int& value) {
        playerComponent->energy = value;
        maxEnergy = value;
    }

    void Update() {
        fireRate = fireRateGui;
        spawnRate = spawnRateGui;
        agentNumbers = agentNumbersGui;
        lifeSpan = agentLifespanGui;
        Physics::showColliders = showCollidersGui;
        SpriteRenderer::showSprites = showSpritesGui;

        if (gameStarted) {
            player->transform.scale = vec3(playerScaleGui);
            playerComponent->velocity = playerSpeedGui;

            totalGameTime += ofGetLastFrameTime();
            currentSpawnTime += ofGetLastFrameTime();

            if (totalGameTime > 120) {
                torpedoAcceleration = 500;
                difficulty = 5;
            }
            else if (totalGameTime > 60) {
                torpedoAcceleration = 400;
                difficulty = 4;
            }
            else if (totalGameTime > 30) {
                torpedoAcceleration = 300;
                difficulty = 3;
            }
            else if (totalGameTime > 10) {
                torpedoAcceleration = 200;
                difficulty = 2;
            }

            if (currentSpawnTime >= spawnRate) {
                currentSpawnTime = 0;

                for (int i = 0; i < agentNumbers; i++) {
                    vec3 pos = vec3(ofRandom(ofGetWindowWidth()), ofRandom(ofGetWindowHeight()), 0);
                    if (distance(pos, player->transform.position) < 200) {
                        i--;
                        continue;
                    }

                    Entity* torpedo = new Entity("Torpedo");
                    torpedo->transform.position = pos;
                    torpedo->transform.rotation = ofRandom(360);
                    Torpedo* component = torpedo->AddComponent<Torpedo>();
                    component->maxLifeTime = lifeSpan;
                    component->target = &player;
                    component->targetCollider = player->GetComponent<Collider2D>();
                    component->i = GameManager::torpedos.size();
                    torp.push_back(component);
                    Collider2D* selfCollider = torpedo->AddComponent<Collider2D>();
                    selfCollider->vertices.clear();
                    selfCollider->vertices.push_back(vec2(-8, -24));
                    selfCollider->vertices.push_back(vec2(-8, 24));
                    selfCollider->vertices.push_back(vec2(8, 24));
                    selfCollider->vertices.push_back(vec2(8, -24));
                    component->selfCollider = selfCollider;
                    GameManager::torpedos.push_back(selfCollider);
                }
            }

            for (int i = 0; i < torp.size(); i++)
            {
                if (torp[i]->destroy)
                {
                    Entity* explosion = new Entity("Explosion");
                    explosion->transform.position = torp[i]->gameObject->transform.position;
                    explosion->AddComponent<Explosion>();
                    torp[i]->gameObject->Destroy();
                    torp.erase(torp.begin() + i);
                    torpedos.erase(torpedos.begin() + i);
                    break;
                }
            }

            if (shooting)
            {
                if (fireTime <= 0) {
                    Entity* bullet = new Entity("Bullet");
                    bullet->transform.position = player->transform.position + player->transform.Up() * 35;
                    bullet->transform.rotation = player->transform.rotation;
                    Bullet* b = bullet->AddComponent<Bullet>();
                    b->p = player->GetComponent<Player>();
                    b->maxEnergy = energyGui;
                    fireTime = fireRate;
                    b->torpedos = &torpedos;
                }
            }

            if (playerComponent->energy <= 0 && !godModeGui)
                End();

            if (fireTime > 0)
                fireTime -= ofGetLastFrameTime();
        }
    }

    void Draw() {
        ofSetColor(ofColor::green);
        if (!gameStarted)
            ofDrawBitmapString("Press Space to Start", ofGetWindowWidth() / 2 - 50, ofGetWindowHeight() / 2);
        else if(gameStarted && player) {
            ofDrawBitmapString("Total time " + to_string(totalGameTime), ofGetWindowWidth() / 2, 30);
            ofDrawBitmapString("Energy level " + to_string(playerComponent->energy) + "|" + to_string(maxEnergy), ofGetWindowWidth() / 2 - 150, 30);
            ofDrawBitmapString("Difficulty " + to_string(difficulty), ofGetWindowWidth() / 2 - 270, 30);
            ofDrawBitmapString("Frame rate " + to_string(ofGetFrameRate()), ofGetWindowWidth() - 200, 30);
        }

        if (debug)
            gui.draw();
    }

    void KeyPressed(int key) {
        if (key == ' ')
            shooting = true;
    }

    void KeyReleased(int key) {
        if (key == ' ')
            shooting = false;
    }

    void End() {
        Entity* boom = new Entity("Player");
        boom->transform.position = player->transform.position;
        Explosion* explosion = boom->AddComponent<Explosion>();
        explosion->strength = 3;
        torpedos.clear();
        torp.clear();
        endLevelAudio.play();
        difficulty = 0;

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
    ofxFloatSlider fireRateGui;
    ofxFloatSlider playerSpeedGui;
    ofxFloatSlider spawnRateGui;
    ofxIntSlider agentNumbersGui;
    ofxFloatSlider agentLifespanGui;
    ofxToggle showCollidersGui = false;
    ofxToggle godModeGui = false;
    ofxToggle showSpritesGui = true;
    ofSoundPlayer startLevelAudio;
    ofSoundPlayer endLevelAudio;
};