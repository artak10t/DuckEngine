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

	// Create moon
	Entity* m = new Entity();
	moon = m->AddComponent<Moon>();

	// Create lander
	Entity* l = new Entity();
	lander = l->AddComponent<Lander>();

	// Create Landing Zones
	Entity* land1 = new Entity();
	land1->transform.position = vec3(0, -20, 0);
	landingZone1 = land1->AddComponent<LandingZone>();
}

void ofApp::update() {
	dragLander();

	//trackingCam.lookAt(lander->transform.position);
	//landerCollider->debugOverlap = landerCollider->aabb.Overlap(platformCollider->aabb);

	// Gui Update
	moon->collider->debugLevel = guiTerrainLevel;

	// Landing Zones Update
	landingZone1->collider->debugOverlap = landingZone1->collider->aabb.Overlap(lander->collider->aabb);
	if (landingZone1->collider->debugOverlap && landingZone1->CheckSpeed(lander->currentSpeed))
		cout << "Landed Successfully" << endl;

	Entity::Update();
}

vec3 delta = vec3(0);
void ofApp::dragLander() {
	vec3 origin = mainCam->getPosition();
	vec3 mouseWorld = mainCam->screenToWorld(glm::vec3(mouseX, mouseY, 0));
	vec3 mouseDir = normalize(mouseWorld - origin);

	lander->collider->debugOverlap = lander->collider->aabb.RayOverlap(Ray(vec3(origin.x, origin.y, origin.z), vec3(mouseDir.x, mouseDir.y, mouseDir.z)), 0, 10000);
	if (drag)
	{
		vec3 mousePos = Ray::GetMousePointOnPlane(*mainCam, vec3(ofGetMouseX(), ofGetMouseY(), 0), lander->gameObject->transform.position, mainCam->getZAxis());
		lander->rigidbody->velocity = vec3(0);
		lander->rigidbody->angularVelocity = vec3(0);
		lander->gameObject->transform.position = mousePos - delta;
	}
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
	ofDrawBitmapString("Fuel: " + to_string(lander->fuel), ofGetWindowWidth() / 2, 30);
	ofDrawBitmapString("Speed: " + to_string(lander->currentSpeed), ofGetWindowWidth() / 2, 60);
	if (!guiHide) gui.draw();
	glDepthMask(true);
}

void ofApp::keyPressed(int key) {
	if (key == 'h') {
		if (mainCam->getMouseInputEnabled()) mainCam->disableMouseInput();
		else mainCam->enableMouseInput();
		guiHide = !guiHide;
	}

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
	if (button == 0 && lander->collider->debugOverlap) {
		vec3 mousePos = Ray::GetMousePointOnPlane(*mainCam, vec3(ofGetMouseX(), ofGetMouseY(), 0), lander->gameObject->transform.position, mainCam->getZAxis());
		delta = mousePos - lander->gameObject->transform.position;
		drag = true;
	}

	Entity::MousePressed(x, y, button);
}

void ofApp::mouseReleased(int x, int y, int button) {
	if (button == 0)
		drag = false;

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