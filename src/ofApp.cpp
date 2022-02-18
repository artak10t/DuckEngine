#include "ofApp.h"
#include "./engine/components/Draggable.h"

void ofApp::setup() {
	//Editor
	inspector.Setup();

	//Need to separate into Scene class
	Entity* object = new Entity();
	object->name = "Triangle";
	object->transform.Position(glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0));
	object->AddComponent<Draggable>();
	Entities.push_back(object);

	inspector.Inspect(object);

	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->Start();
}

void ofApp::update() {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->Update();
}

void ofApp::draw() {
	inspector.Draw();

	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->Draw();
}

void ofApp::keyPressed(int key) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->KeyPressed(key);
}

void ofApp::keyReleased(int key) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->KeyReleased(key);
}

void ofApp::mouseMoved(int x, int y) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->MouseMoved(x, y);
}

void ofApp::mouseDragged(int x, int y, int button) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->MouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->MousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->MouseReleased(x, y, button);
}

void ofApp::mouseEntered(int x, int y) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->MouseEntered(x, y);
}

void ofApp::mouseExited(int x, int y) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->MouseExited(x, y);
}

void ofApp::windowResized(int w, int h) {
	for (int i = 0; i < Entities.size(); i++)
		Entities[i]->WindowResized(w, h);
}

void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}

ofApp::~ofApp() {
	for (int i = 0; i < Entities.size(); i++) {
		Entities[i]->RemoveAllComponents();
		delete Entities[i];
	}
}