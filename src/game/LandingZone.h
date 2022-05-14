#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/components/BoxCollider.h"

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
    bool VerifyLanding(float speed) {
        if (speed <= 0.3 && !landed) {
            float score = 1;
            score /= speed;

            if(speed <= 0.1)
                cout << "Soft landing, your score is: " << score << endl;
            else
                cout << "Heavy landing, your score is: " << score << endl;

            landed = true;
            return true;
        }

        return false;
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
        ofPopMatrix();
        ofDisableDepthTest();
    }

private:
};