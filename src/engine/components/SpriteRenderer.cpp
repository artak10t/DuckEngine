#include "SpriteRenderer.h"
bool SpriteRenderer::showSprites = true;

void SpriteRenderer::Update() {
	scaledWidth = sprite.getWidth() * scale.x;
	scaledHeight = sprite.getHeight() * scale.y;
}

void SpriteRenderer::Draw() {
	if (!showSprites)
		return;

	ofPushMatrix();
	ofEnableAlphaBlending();
	ofSetColor(color);
	ofMultMatrix(gameObject->transform.Matrix4());
	sprite.draw(-scaledWidth / 2, -scaledHeight / 2, scaledWidth, scaledHeight);
	ofDisableAlphaBlending();
	ofPopMatrix();
}