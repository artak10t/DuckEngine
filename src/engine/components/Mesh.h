#pragma once
#include "../Component.h"
#include "../Entity.h"
#include "../engine/Physics.h"
#include "ofxAssimpModelLoader.h"
#include <gl/ofLight.h>
#include <graphics/ofImage.h>

class Mesh : public Component
{
public:
    using Component::Component;
    ofMaterial Material;
    bool visible = true;

    void LoadModel(string path);
    void LoadTexture(string path);
    ofMesh getMesh();

    void Draw();
private:
    ofMesh mesh;
    ofTexture texture;
};