#include "ofApp.h"
#include "./engine/components/Draggable.h"
#include "./engine/components/Controller.h"
#include "./engine/components/Mesh.h"

void ofApp::setup() {
	inspector.Setup();

	Entity* object = new Entity();
	object->name = "Triangle";
	object->transform.position = glm::vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
	object->AddComponent<Mesh>();
	object->AddComponent<Draggable>();
	object->AddComponent<Controller>();
	Entity::Instantiate(object);

	inspector.Inspect(object);

	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->Start();
}

void ofApp::update() {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->Update();
}

void ofApp::draw() {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->Draw();

	inspector.Draw();
}

void ofApp::keyPressed(int key) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->KeyPressed(key);
}

void ofApp::keyReleased(int key) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->KeyReleased(key);
}

void ofApp::mouseMoved(int x, int y) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->MouseMoved(x, y);
}

void ofApp::mouseDragged(int x, int y, int button) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->MouseDragged(x, y, button);
}

void ofApp::mousePressed(int x, int y, int button) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->MousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->MouseReleased(x, y, button);
}

void ofApp::mouseEntered(int x, int y) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->MouseEntered(x, y);
}

void ofApp::mouseExited(int x, int y) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->MouseExited(x, y);
}

void ofApp::windowResized(int w, int h) {
	for (int i = 0; i < Entity::gameObjects.size(); i++)
		Entity::gameObjects[i]->WindowResized(w, h);
}

void ofApp::gotMessage(ofMessage msg) {

}

void ofApp::dragEvent(ofDragInfo dragInfo) {

}

ofApp::~ofApp() {
	for (int i = 0; i < Entity::gameObjects.size(); i++) {
		Entity::gameObjects[i]->RemoveAllComponents();
		delete Entity::gameObjects[i];
	}
}