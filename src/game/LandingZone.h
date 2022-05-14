#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/components/BoxCollider.h"

class LandingScore {
public:
    LandingScore()
    {
        softLanding = false;
        heavyLanding = false;
        score = 0;
    }

    bool softLanding = false;
    bool heavyLanding = false;
    float score = 0;
};

class LandingZone : public Component
{
public:
    using Component::Component;
    BoxCollider* collider;
    bool landed = false;

    void Start() {
        // Use boxCollider as trigger.
        collider = gameObject->AddComponent<BoxCollider>();
        collider->Init(vec3(0, 0, 0), vec3(30, 3, 30));
    }

    // For landing score we take 1 and divide by speed
    LandingScore VerifyLanding(float speed) {
        LandingScore landingResult;

        if (speed <= 0.3 && !landed) {
            landed = true;
            float score = 1;
            score /= speed;
            landingResult.score = score;

            if (speed <= 0.1)
                landingResult.softLanding = true;
            else
                landingResult.heavyLanding = true;
        }

        return landingResult;
    }

    // Draw landing zone
    void Draw() {
        if (landed)
            return;

        ofEnableDepthTest();
        ofPushMatrix();
        ofMultMatrix(gameObject->transform.Matrix4());
        ofSetColor(0, 255, 0, 50);
        vec3 min = collider->aabb.parameters[0];
        vec3 max = collider->aabb.parameters[1];
        vec3 size = max - min;
        vec3 center = size / 2 + min;
        ofVec3f p = ofVec3f(center.x, center.y, center.z);
        float w = size.x;
        float h = size.y;
        float d = size.z;
        ofDrawBox(p, w, h, d);
        ofSetColor(255, 0, 0, 50);
        ofSetLineWidth(3);
        ofDrawArrow(vec3(15, 25, 15), vec3(15, 5, 15), 1);
        ofPopMatrix();
        ofDisableDepthTest();
    }

private:
};