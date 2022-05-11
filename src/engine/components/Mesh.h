#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "ofxAssimpModelLoader.h"
#include <gl/ofLight.h>
#include <graphics/ofImage.h>

class Mesh : public Component
{
public:
    using Component::Component;
    void LoadModel(string path);
    void LoadTexture(string path);

    void Draw();
private:
    ofxAssimpModelLoader assimp;
    ofMesh mesh;
    ofTexture texture;
};