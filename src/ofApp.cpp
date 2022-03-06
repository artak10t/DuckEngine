#include "ofApp.h"
#include "./engine/components/Draggable.h"
#include "./engine/components/Controller.h"
#include "./engine/components/Mesh.h"
#include "./engine/components/Spawner.h"

void ofApp::setup() {
	inspector.Setup();

	Entity* manager = new Entity();
	manager->AddComponent<Spawner>();

	Entity* player = new Entity();
	player->name = "Player";
	player->transform.position = vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
	player->AddComponent<Mesh>();
	player->AddComponent<Controller>();
	player->AddComponent<Draggable>();

	//inspector.Inspect(object);
}

void ofApp::update() {
	Entity::Update();
}

void ofApp::draw() {
	Entity::Draw();

	//inspector.Draw();
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