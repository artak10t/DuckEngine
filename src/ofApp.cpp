#include "ofApp.h"

void ofApp::setup() {
	ofSetVerticalSync(true);

	// Setup Gui
	gui.setup();
	gui.add(guiTerrainLevel.setup("Number of Terrain Levels", 20, 15, 20));
	gui.add(guiShowColliders.setup("Show Colliders", false));
	gui.add(guiShowAltimeter.setup("Show Altimeter", false));
	gui.add(guiShowAxis.setup("Show Axis", false));

	// Setup cameras
	downCam.lookAt(vec3(0, -1, 0));
	downCam.rotate(180, vec3(0, 1, 0));
	downCam.setDistance(10);
	downCam.setFarClip(30000);
	downCam.setNearClip(0.1);
	downCam.setFov(90);

	trackingCam.setPosition(0, 0, 0);
	trackingCam.lookAt(vec3(0, 0, -1));
	trackingCam.setDistance(100);
	trackingCam.setFarClip(30000);
	trackingCam.setNearClip(0.1);
	trackingCam.setFov(65.5);
	mainCam = &trackingCam;

	// Setup lights
	ambientLight.setAmbientColor(ofFloatColor::dimGray);
	directionalLight.setDirectional();
	directionalLight.rotate(76, 1, 1, 1);

	// Create moon
	Entity* m = new Entity();
	moon = m->AddComponent<Moon>();
	Physics::gravity = vec3(0, -0.1, 0);

	// Create sky
	Entity* s = new Entity();
	s->AddComponent<Sky>();

	// Create lander
	Entity* l = new Entity();
	l->transform.position = vec3(-10, 0, 10);
	lander = l->AddComponent<Lander>();

	// Create Landing Zones
	Entity* land1 = new Entity();
	land1->transform.position = vec3(-50, -28, -30);
	landingZone1 = land1->AddComponent<LandingZone>();
}

void ofApp::update() {
	dragLander();

	//trackingCam.lookAt(lander->transform.position);

	// Gui Update
	moon->collider->debugLevel = guiTerrainLevel;
	Physics::showColliders = guiShowColliders;
	if (guiShowAxis)
		Physics::showAxis = Axis::Local;
	else
		Physics::showAxis = Axis::None;

	// Altitude
	altitudePoint = landerRay();
	altitude = abs(lander->gameObject->transform.position.y - altitudePoint.y);

	// Landing Zones Update
	landingZone1->collider->debugOverlap = landingZone1->collider->aabb.Intersect(lander->collider->aabb);
	if (landingZone1->collider->debugOverlap)
		landingZone1->VerifyLanding(lander->currentSpeed);

	// Moon and lander collision
	moonCollisions.clear();
	moon->collider->IntersectAABB(lander->collider->aabb, moon->collider->root, moonCollisions);
	if (altitude < 1) {
		lander->gameObject->transform.position = vec3(lander->gameObject->transform.position.x, altitudePoint.y + 1, lander->gameObject->transform.position.z);
		vec3 force = 1 * (dot(-lander->rigidbody->velocity, vec3(0, 1, 0)) * vec3(0, 1, 0));
		lander->rigidbody->velocity = lander->rigidbody->velocity * vec3(1, -0.8, 1);
		lander->rigidbody->AddForce(force);
	}

	// Calculate delta rotation for camera to rotate
	float oldY = lander->gameObject->transform.rotation.y;
	Entity::Update();
	float delta = lander->gameObject->transform.rotation.y - oldY;

	// Cameras updates
	downCam.setPosition(lander->gameObject->transform.position + vec3(0, -0.5, 0));
	downCam.rotate(delta, vec3(0, 1, 0));
}

vec3 delta = vec3(0);
void ofApp::dragLander() {
	vec3 origin = mainCam->getPosition();
	vec3 mouseWorld = mainCam->screenToWorld(glm::vec3(mouseX, mouseY, 0));
	vec3 mouseDir = normalize(mouseWorld - origin);

	lander->collider->debugOverlap = lander->collider->aabb.IntersectRay(Ray(vec3(origin.x, origin.y, origin.z), vec3(mouseDir.x, mouseDir.y, mouseDir.z)), 0, 10000);
	if (drag && !guiHide)
	{
		vec3 mousePos = Ray::GetMousePointOnPlane(*mainCam, vec3(ofGetMouseX(), ofGetMouseY(), 0), lander->gameObject->transform.position, mainCam->getZAxis());
		lander->rigidbody->velocity = vec3(0);
		lander->rigidbody->angularVelocity = vec3(0);
		lander->gameObject->transform.position = mousePos - delta;
	}
}

/*
	Uses raycasting to find altitude.
*/
vec3 ofApp::landerRay() {
	vec3 rayPoint = lander->gameObject->transform.position;
	vec3 rayDir = -lander->gameObject->transform.Up();
	normalize(rayDir);
	Ray ray = Ray(vec3(rayPoint.x, rayPoint.y, rayPoint.z), vec3(rayDir.x, rayDir.y, rayDir.z));

	TreeNode selectedNode;
	bool pointSelected = moon->collider->IntersectRay(ray, moon->collider->root, selectedNode);

	if (pointSelected) {
		vec3 pointRet = moon->mesh->getMesh().getVertex(selectedNode.points[0]);
		return pointRet;
	}
	else
		return vec3(0);
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

	// Moon collisions show
	if (Physics::showColliders) {
		ofDisableLighting();
		ofEnableDepthTest();
		ofPushMatrix();
		ofNoFill();
		ofSetColor(ofColor::lightBlue);
		for (int i = 0; i < moonCollisions.size(); i++) {
			vec3 min = moonCollisions[i].parameters[0];
			vec3 max = moonCollisions[i].parameters[1];
			vec3 size = max - min;
			vec3 center = size / 2 + min;
			ofVec3f p = ofVec3f(center.x, center.y, center.z);
			float w = size.x;
			float h = size.y;
			float d = size.z;
			ofDrawBox(p, w, h, d);
		}
		ofPopMatrix();
		ofDisableDepthTest();
		ofEnableLighting();
	}

	if (guiShowAltimeter) {
		ofEnableDepthTest();
		ofSetColor(ofColor::red);
		ofDrawSphere(altitudePoint, 0.25);
		ofDisableDepthTest();
	}

	Entity::Draw();

	directionalLight.disable();
	ambientLight.disable();
	if (mainCam != NULL)
		mainCam->end();

	glDepthMask(false);
	ofSetColor(ofColor::white);
	ofDrawBitmapString("Fuel: " + to_string(lander->fuel), ofGetWindowWidth() / 2, 30);
	ofDrawBitmapString("Speed: " + to_string(lander->currentSpeed), ofGetWindowWidth() / 2, 60);
	ofDrawBitmapString("Altitude: " + to_string(altitude), ofGetWindowWidth() / 2, 90);
	ofDrawBitmapString("Fps: " + to_string(ofGetFrameRate()), ofGetWindowWidth() - 180, 30);
	if (!guiHide) gui.draw();
	glDepthMask(true);
}

void ofApp::keyPressed(int key) {
	if (key == 'h') {
		if (mainCam->getMouseInputEnabled()) mainCam->disableMouseInput();
		else mainCam->enableMouseInput();
		guiHide = !guiHide;
	}

	if (key == OF_KEY_F1)
		mainCam = &downCam;

	if (key == OF_KEY_F2)
		mainCam = &sideCam;

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