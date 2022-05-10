#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "ofxAssimpModelLoader.h"

class Mesh : public Component
{
public:
    using Component::Component;
    void LoadModel(string path);

    void Draw();
private:
    ofxAssimpModelLoader assimp;
};