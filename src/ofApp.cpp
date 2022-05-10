#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);

	// Setup main camera
	trackingCam.setPosition(0, 0, 0);
	trackingCam.lookAt(glm::vec3(0, 0, -1));
	trackingCam.setDistance(100);
	trackingCam.setNearClip(0.1);
	trackingCam.setFov(65.5);
	mainCam = &trackingCam;

	// Setup lights
	ambientLight.setAmbientColor(ofFloatColor::black);
	directionalLight.setDirectional();
	directionalLight.rotate(45, 1, 1, 1);

	// Create entity lander
	lander = new Entity();
	lander->transform.scale = vec3(5, 5, 5);
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
	ambientLight.enable();
	directionalLight.enable();

	Entity::Draw();

	directionalLight.disable();
	ambientLight.disable();
	if (mainCam != NULL)
		mainCam->end();
}

void ofApp::keyPressed(int key) {
	if (key == 'w')
		lander->transform.rotation += vec3(1, 0, 0);
	else if (key == 's')
		lander->transform.rotation += vec3(-1, 0, 0);

	if (key == 'q')
		lander->transform.rotation += vec3(0, 1, 0);
	else if (key == 'e')
		lander->transform.rotation += vec3(0, -1, 0);

	if (key == 'a')
		lander->transform.rotation += vec3(0, 0, 1);
	else if (key == 'd')
		lander->transform.rotation += vec3(0, 0, -1);

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