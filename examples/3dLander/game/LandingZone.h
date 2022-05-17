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
        collider->Init(vec3(0, 0, 0), vec3(10, 3, 10));
    }

    // For landing score we take 1 and divide by speed
    LandingScore VerifyLanding(float speed) {
        LandingScore landingResult;

        if (speed <= 0.15 && !landed) {
            landed = true;
            float score = 1;
            score /= speed;
            landingResult.score = score;

            if (speed <= 0.075)
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
        ofFill();
        ofMultMatrix(gameObject->transform.Matrix4());
        ofSetColor(255, 0, 0, 50);
        ofSetLineWidth(3);
        ofDrawArrow(vec3(5, 25, 5), vec3(5, 5, 5), 1);
        ofPopMatrix();
        ofDisableDepthTest();
    }

private:
};