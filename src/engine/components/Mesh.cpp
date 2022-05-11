#include "Mesh.h"

void Mesh::LoadModel(string path) {
	assimp.loadModel(path);
	assimp.setScaleNormalization(false);
}

void Mesh::LoadTexture(string path) {
	ofDisableArbTex();
	ofLoadImage(texture, path);
	texture.setTextureWrap(GL_REPEAT, GL_REPEAT);
	texture.generateMipmap();
	texture.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
}

void Mesh::Draw() {
	ofEnableDepthTest();
	ofEnableSmoothing();
	ofDisableLighting();

	if (gameObject->transform.debugAxis == DebugAxis::Global)
	{
		ofSetLineWidth(5);
		ofSetColor(ofColor::red);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + vec3(5, 0, 0) * gameObject->transform.scale);
		ofSetColor(ofColor::green);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + vec3(0, 5, 0) * gameObject->transform.scale);
		ofSetColor(ofColor::blue);
		ofDrawLine(gameObject->transform.position, gameObject->transform.position + vec3(0, 0, 5) * gameObject->transform.scale);
	}
	else if (gameObject->transform.debugAxis == DebugAxis::Local) {
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
	assimp.drawFaces();
	texture.unbind();
	ofPopMatrix();
	ofDisableDepthTest();
	ofDisableSmoothing();
	ofDisableLighting();
}