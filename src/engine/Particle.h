#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <app/ofAppRunner.h>
using namespace glm;
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
};