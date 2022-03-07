#include "ofApp.h"
#include "./game/Player.h"
#include "./game/Smoke.h"
#include "./game/Torpedo.h"
#include "./engine/components/Spawner.h"

void ofApp::setup() {
	Entity* player = new Entity();
	player->name = "Player";
	player->transform.position = vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
	player->AddComponent<Player>();

	Entity* spawner = new Entity();
	spawner->AddComponent<Spawner>()->player = player;
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