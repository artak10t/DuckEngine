#include "ofApp.h"

void ofApp::setup() {
	backgroundSprite.load("background.png");
	gameManager.Setup();
}

void ofApp::update() {
	gameManager.Update();
	Entity::Update();
}

void ofApp::draw() {
	ofSetColor(ofColor::white);
	for (int i = 0; i < ofGetScreenHeight(); i += backgroundSprite.getHeight()) {
		for (int j = 0; j < ofGetScreenWidth(); j += backgroundSprite.getWidth()) {
			backgroundSprite.draw(j, i, backgroundSprite.getWidth(), backgroundSprite.getHeight());
		}
	}

	Entity::Draw();
	gameManager.Draw();
}

void ofApp::keyPressed(int key) {
	if (key == ' ')
		gameManager.Start();
	if (key == 'h' && !gameManager.debug)
		gameManager.debug = true;
	else if (key == 'h' && gameManager.debug)
		gameManager.debug = false;

	gameManager.KeyPressed(key);

	Entity::KeyPressed(key);
}

void ofApp::keyReleased(int key) {
	gameManager.KeyReleased(key);
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