#pragma once
#include <glm/glm.hpp>
using namespace glm;
enum class Axis { None, Local, Global };

class Physics
{
public:
	static bool showColliders;
	static Axis showAxis;
	static bool enablePhysics;
	static vec3 gravity;
};

