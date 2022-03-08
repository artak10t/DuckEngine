#include "Collider2D.h"

void Collider2D::Start() {
	vertices.push_back(vec2(-24, -24));
	vertices.push_back(vec2(-24, 24));
	vertices.push_back(vec2(24, 24));
	vertices.push_back(vec2(24, -24));

	for (int i = 0; i < vertices.size(); i++)
		verticesWorldSpace.push_back(gameObject->transform.Matrix4() * vec4(vertices[i], 1, 1));
}

void Collider2D::Update() {
	for (int i = 0; i < vertices.size(); i++)
		verticesWorldSpace[i] = gameObject->transform.Matrix4() * vec4(vertices[i], 1, 1);
}

void Collider2D::Draw() {
	if (!debug)
		return;

	if (!overlap)
		ofSetColor(ofColor::green);
	else
		ofSetColor(ofColor::red);
	colliderVisual.clear();
	for(int i = 0; i < verticesWorldSpace.size(); i++)
		colliderVisual.addVertex(ofPoint(verticesWorldSpace[i].x, verticesWorldSpace[i].y));

	colliderVisual.addVertex(ofPoint(verticesWorldSpace[0].x, verticesWorldSpace[0].y));
	colliderVisual.draw();
}

bool Collider2D::CollisionCheck(Collider2D& collider1, Collider2D& collider2) {
	Collider2D* polyline1 = &collider1;
	Collider2D* polyline2 = &collider2;

	for (int shape = 0; shape < 2; shape++) {
		if (shape == 1) {
			polyline1 = &collider2;
			polyline2 = &collider1;
		}

		for (int p = 0; p < polyline1->verticesWorldSpace.size(); p++) {
			vec2 lineR1s = polyline1->gameObject->transform.position;
			vec2 lineR1e = polyline1->verticesWorldSpace[p];

			for (int q = 0; q < polyline2->verticesWorldSpace.size(); q++) {
				vec2 lineR2s = polyline2->verticesWorldSpace[q];
				vec2 lineR2e = polyline2->verticesWorldSpace[(q + 1) % polyline2->verticesWorldSpace.size()];

				float h = (lineR2e.x - lineR2s.x) * (lineR1s.y - lineR1e.y) - (lineR1s.x - lineR1e.x) * (lineR2e.y - lineR2s.y);
				float t1 = ((lineR2s.y - lineR2e.y) * (lineR1s.x - lineR2s.x) + (lineR2e.x - lineR2s.x) * (lineR1s.y - lineR2s.y)) / h;
				float t2 = ((lineR1s.y - lineR1e.y) * (lineR1s.x - lineR2s.x) + (lineR1e.x - lineR1s.x) * (lineR1s.y - lineR2s.y)) / h;

				if (t1 >= 0 && t1 < 1 && t2 >= 0 && t2 < 1)
					return true;
			}
		}
	}

	return false;
}