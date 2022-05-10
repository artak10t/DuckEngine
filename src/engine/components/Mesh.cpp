#include "Mesh.h"

void Mesh::LoadModel(string path) {
	assimp.loadModel(path);
	assimp.setScaleNormalization(false);
}

void Mesh::Draw() {
	ofPushMatrix();
	ofMultMatrix(gameObject->transform.Matrix4());
	assimp.drawFaces();
	ofPopMatrix();
}