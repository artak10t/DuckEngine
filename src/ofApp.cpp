#include "ofApp.h"
#include "./game/Player.h"
#include "./game/Torpedo.h"
#include "./engine/components/SpriteRenderer.h"

void ofApp::setup() {
	inspector.Setup();

	Entity* player = new Entity();
	player->name = "Player";
	player->transform.position = vec3(ofGetWindowWidth() / 2.0, ofGetWindowHeight() / 2.0, 0);
	player->AddComponent<Player>();
	SpriteRenderer* playerRenderer = player->AddComponent<SpriteRenderer>();
	playerRenderer->sprite.load("player.png");
	playerRenderer->scale = vec2(3, 3);
	playerRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	Entity* torpedo = new Entity();
	torpedo->name = "Torpedo";
	torpedo->transform.position = vec3(400, 200, 0);
	Torpedo* torpedoComponent = torpedo->AddComponent<Torpedo>();
	torpedoComponent->player = player;
	torpedoComponent->state = State::Following;
	SpriteRenderer* torpedoRenderer = torpedo->AddComponent<SpriteRenderer>();
	torpedoRenderer->sprite.load("torpedo.png");
	torpedoRenderer->scale = vec2(3, 3);
	torpedoRenderer->sprite.getTexture().setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);

	//inspector.Inspect(object);
}

void ofApp::update() {
	Entity::Update();
}

void ofApp::draw() {
	Entity::Draw();

	//inspector.Draw();
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