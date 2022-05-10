#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);

	// Setup main camera
	trackingCam.setPosition(0, 0, 0);
	trackingCam.lookAt(glm::vec3(0, 0, 1));
	trackingCam.setDistance(100);
	trackingCam.setNearClip(0.1);
	trackingCam.setFov(65.5);
	mainCam = &trackingCam;

	// Create entity lander
	Entity* lander = new Entity();
	// Add mesh component and load model
	lander->AddComponent<Mesh>()->LoadModel("models/cube.obj");
}

void ofApp::update() {
	Entity::Update();
}

/* 
	Some components use draw method, such as Mesh.
	We draw everything inside camera transformation.
	GUI drawings also go here.
*/
void ofApp::draw() {
	ofBackground(backgroundColor);
	if(mainCam != NULL)
		mainCam->begin();

	ofEnableLighting();
	Entity::Draw();

	if (mainCam != NULL)
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