#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../Particle.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <gl/ofShader.h>
#include <gl/ofVbo.h>
#include <graphics/ofGraphics.h>
#include <graphics/of3dGraphics.h>
#include <app/ofAppRunner.h>
using namespace glm;

class ParticleSystem : public Component
{
public:
    using Component::Component;
    ofShader Shader;
    vec3 InitialForces = vec3(0, 10, 0);
    vec3 RandomForces = vec3(1);
    vec3 Turbulence = vec3(0);
    vec3 Origin = vec3(0);
    int Limit = 30;
    float SpawnRate = 0.01;
    float LifeTime = 1;
    float InitialScale = 1;
    float FinalScale = 1;
    bool WorldSpace = true;
    bool Enable = true;

    void ShotAll();
    void Update();
    void Draw();

private:
    void spawnParticle();
    void destroyParticle();
    void loadVBO();
    ofVbo vbo;
    float currentSpawnRate = 0;
    vector<Particle> particles;
    mat4 matrix4(int particle);
};