#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);

	// Setup Gui
	gui.setup();
	gui.add(guiTerrainLevel.setup("Number of Terrain Levels", 20, 15, 20));
	Physics::showColliders = true;

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
	directionalLight.rotate(76, 1, 1, 1);

	// Create lander
	Entity* l = new Entity();
	l->AddComponent<Lander>();

	// TEST PLATFORM
	platform = new Entity();
	platform->transform.position = vec3(0, 10, 0);
	platformCollider = platform->AddComponent<BoxCollider>();
	platformCollider->Init(vec3(0, 0, 0), vec3(20, 5, 20));
	platform->transform.rotation = vec3(10, 34, 32);

	// Create moon
	moon = new Entity();
	Mesh* moonMesh = moon->AddComponent<Mesh>();
	moonMesh->LoadModel("models/moon.obj");
	moonMesh->LoadTexture("models/moon.png");
	moonMesh->Material.setShininess(0.01);
	moonCollider = moon->AddComponent<TerrainCollider>();
	moonCollider->Init(20);
}

void ofApp::update() {
	vec3 origin = trackingCam.getPosition();
	vec3 mouseWorld = trackingCam.screenToWorld(glm::vec3(mouseX, mouseY, 0));
	vec3 mouseDir = normalize(mouseWorld - origin);

	//trackingCam.lookAt(lander->transform.position);
	//landerCollider->debugOverlap = landerCollider->aabb.RayOverlap(Ray(vec3(origin.x, origin.y, origin.z), vec3(mouseDir.x, mouseDir.y, mouseDir.z)), 0, 10000);
	//landerCollider->debugOverlap = landerCollider->aabb.Overlap(platformCollider->aabb);

	moonCollider->debugLevel = guiTerrainLevel;

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

	glDepthMask(false);
	if (!guiHide) gui.draw();
	glDepthMask(true);
}

void ofApp::keyPressed(int key) {
	if (key == 'h')
		guiHide = !guiHide;

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