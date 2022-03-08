#include "SpriteRenderer.h"

void SpriteRenderer::Update() {
	scaledWidth = sprite.getWidth() * scale.x;
	scaledHeight = sprite.getHeight() * scale.y;
}

void SpriteRenderer::Draw() {
	ofPushMatrix();
	ofSetColor(color);
	ofMultMatrix(gameObject->transform.Matrix4());
	sprite.draw(-scaledWidth / 2, -scaledHeight / 2, scaledWidth, scaledHeight);
	ofPopMatrix();
}