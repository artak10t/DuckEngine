#include "ofApp.h"

// Use for initial setup of entities and components
void ofApp::setup() {
	ofSetVerticalSync(true);

	freeCam.lookAt(vec3(0, 0, -1));
	freeCam.setDistance(50);
	freeCam.setFarClip(1000);
	freeCam.setNearClip(0.1);
	freeCam.setFov(70);
	mainCam = &freeCam;
}

void ofApp::update() {
	Entity::Update();
}

void ofApp::draw() {
	ofBackground(backgroundColor);

	// Enable cameras and lights
	// For 2D game delete the lines below except Entity::draw();
	mainCam->begin();
	ambientLight.enable();
	directionalLight.enable();

	Entity::Draw();

	directionalLight.disable();
	ambientLight.disable();
	mainCam->end();
}

void ofApp::keyPressed(int key) {
	Entity::KeyPressed(key);
}

void ofApp::keyReleased(int key) {
	Entity::KeyReleased(key);
}

void ofApp::mouseMoved(int x, int y) {
	Entity::MouseMoved(x, y);
}

void ofApp::mouseDragged(int x, int y, int button) {
	Entity::MouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button) {
	Entity::MousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button) {
	Entity::MouseReleased(x, y, button);
}

void ofApp::mouseEntered(int x, int y) {
	Entity::MouseEntered(x, y);
}

void ofApp::mouseExited(int x, int y) {
	Entity::MouseExited(x, y);
}

void ofApp::windowResized(int w, int h) {
	Entity::WindowResized(w, h);
}

void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}

ofApp::~ofApp() {
	Entity::Clear();
}