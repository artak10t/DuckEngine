#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);

	// Setup main camera
	trackingCam.setPosition(0, 0, 0);
	trackingCam.lookAt(glm::vec3(0, 0, -1));
	trackingCam.setDistance(100);
	trackingCam.setFarClip(30000);
	trackingCam.setNearClip(0.1);
	trackingCam.setFov(65.5);
	mainCam = &trackingCam;

	// Setup lights
	ambientLight.setAmbientColor(ofFloatColor::black);
	directionalLight.setDirectional();
	directionalLight.rotate(45, 1, 1, 1);

	// Create entity lander
	lander = new Entity();
	lander->transform.debugAxis = DebugAxis::Local;
	Mesh* landerMesh = lander->AddComponent<Mesh>();
	landerMesh->LoadModel("models/lander.obj");
	landerMesh->LoadTexture("models/moon.png");
	landerRigidbody = lander->AddComponent<Rigidbody>();
	landerRigidbody->gravityForce = vec3(0, 0, 0);
	landerRigidbody->drag = 1;

	// Create entity moon
	moon = new Entity();
	moon->transform.scale = vec3(5);
	Mesh* moonMesh = moon->AddComponent<Mesh>();
	moonMesh->LoadModel("models/moon.obj");
	moonMesh->LoadTexture("models/moon.png");
}

void ofApp::update() {
	Entity::Update();

	trackingCam.lookAt(lander->transform.position);
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
	if (key == 'q')
		landerRigidbody->AddTorque(vec3(0, 10, 0));
	else if (key == 'e')
		landerRigidbody->AddTorque(vec3(0, -10, 0));

	if (key == ' ')
		landerRigidbody->AddForce(lander->transform.Up() * 10);

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