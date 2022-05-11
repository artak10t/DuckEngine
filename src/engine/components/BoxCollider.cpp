#include "BoxCollider.h"

void BoxCollider::Init(vec3 min, vec3 max) {
	aabb.parameters[0] = min;
	aabb.parameters[1] = max;
	vec3 size = aabb.Max() - aabb.Min();
	vec3 center = aabb.Center();
	p = ofVec3f(center.x, center.y, center.z);
	w = size.x;
	h = size.y;
	d = size.z;
}

void BoxCollider::Start() {
	
}

void BoxCollider::Update() {

}

void BoxCollider::Draw() {
	if (!Physics::showColliders)
		return;

	ofDisableLighting();
	ofEnableDepthTest();
	ofPushMatrix();
	ofMultMatrix(gameObject->transform.Matrix4());
	ofNoFill();
	ofSetColor(ofColor::green);
	ofDrawBox(p, w, h, d);
	ofPopMatrix();
	ofDisableDepthTest();
	ofEnableLighting();
}