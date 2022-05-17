#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <app/ofAppRunner.h>
using namespace glm;

/*
    Individual particle class. 
    Used with particle system for position calculation of
    the particle using a physics.
*/
class Particle
{
public:
    void Update();

    float drag = 0.99;
    float scale = 1;
    vec3 velocity = vec3(0);
    vec3 acceleration = vec3(0);
	vec3 position = vec3(0);
    vec3 forces = vec3(0);
    float currentLifeTime = 0;
};