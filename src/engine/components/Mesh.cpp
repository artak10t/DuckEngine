#include "Mesh.h"

void Mesh::LoadModel(string path) {
	ofxAssimpModelLoader assimp;
	assimp.loadModel(path);
	assimp.setScaleNormalization(false);
	mesh = assimp.getMesh(0);
}

void Mesh::LoadTexture(string path) {
	ofDisableArbTex();
	ofLoadImage(texture, path);
	texture.generateMipmap();
	texture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
}

ofMesh Mesh::getMesh() {
	return mesh;
}

void Mesh::Draw() {
	if (!visible)
		return;

	ofEnableDepthTest();
	ofEnableSmoothing();
	ofDisableLighting();

	// Depeding if physics show axis is set
	// draw local or global axis.
	if (Physics::showAxis == Axis::Global)
	{
		ofSetLineWidth(5);
		ofSetColor(ofColor::red);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + vec3(5, 0, 0) * gameObject->transform.scale);
		ofSetColor(ofColor::green);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + vec3(0, 5, 0) * gameObject->transform.scale);
		ofSetColor(ofColor::blue);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + vec3(0, 0, 5) * gameObject->transform.scale);
	}
	else if (Physics::showAxis == Axis::Local) {
		ofSetLineWidth(5);
		ofSetColor(ofColor::red);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + gameObject->transform.Right() * 5 * gameObject->transform.scale);
		ofSetColor(ofColor::green);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + gameObject->transform.Up() * 5 * gameObject->transform.scale);
		ofSetColor(ofColor::blue);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + gameObject->transform.Forward() * 5 * gameObject->transform.scale);
	}

	ofEnableLighting();
	ofPushMatrix();
	ofMultMatrix(gameObject->transform.Matrix4());
	texture.bind();
	Material.begin();
	mesh.draw();
	Material.end();
	texture.unbind();
	ofPopMatrix();
	ofDisableDepthTest();
	ofDisableSmoothing();
	ofDisableLighting();
}