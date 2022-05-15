#pragma once
#include "ofMain.h"
#include "ofxGui.h"
#include "engine/Entity.h"
#include "engine/components/Mesh.h"
#include "engine/components/Rigidbody.h"
#include "engine/components/BoxCollider.h"
#include "engine/components/TerrainCollider.h"
#include "game/Lander.h"
#include "game/Moon.h"
#include "game/LandingZone.h"
#include "game/Sky.h"
using namespace glm;

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void dragLander();
	vec3 landerRay();

	ofEasyCam* mainCam;
	ofEasyCam trackingCam;
	ofEasyCam downCam;
	ofEasyCam sideCam;
	ofLight ambientLight;
	ofLight directionalLight;

	vector<AABB> moonCollisions;
	Lander* lander;
	Moon* moon;
	LandingZone* landingZone1;
	LandingZone* landingZone2;
	LandingZone* landingZone3;
	vec3 altitudePoint = vec3(0);
	float altitude = 0;

	ofColor backgroundColor = ofColor::black;

	// Gui
	ofxPanel gui;
	ofxIntSlider guiTerrainLevel;
	ofxToggle guiShowColliders = false;
	ofxToggle guiShowAltimeter = false;
	ofxToggle guiShowAxis = false;
	string score1 = "";
	string score2 = "";
	string score3 = "";

	// Keys
	bool guiHide = true;
	bool drag = false;

	~ofApp();
};