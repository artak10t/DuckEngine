#include "Inspector.h"

void Inspector::Setup() {
	gui.setup();
}

void Inspector::Inspect(Entity* entity) {
	if (entity == NULL) {
		this->entity = NULL;
		return;
	}
	this->entity = entity;
	gui.setName(entity->name);
	gui.add(localSpace.setup("Local Space", false));
	gui.add(isActive.setup("Is Active", entity->isActive));

	position.setName("Position");
	position.add(positionX.set("X", entity->transform.Position().x));
	position.add(positionY.set("Y", entity->transform.Position().y));
	position.add(positionZ.set("Z", entity->transform.Position().z));

	gui.add(position);
}

void Inspector::Draw() {
	if (this->entity == NULL)
		return;
	
	DrawSpaceAxis();

	gui.draw();
}

void Inspector::DrawSpaceAxis() {
	if (localSpace) {
		ofSetColor(ofColor::blue);
		ofDrawLine(this->entity->transform.Position(), this->entity->transform.Position() + this->entity->transform.Up() * 100 * this->entity->transform.Scale().x);
		ofSetColor(ofColor::red);
		ofDrawLine(this->entity->transform.Position(), this->entity->transform.Position() + this->entity->transform.Right() * 100 * this->entity->transform.Scale().y);
	} else {
		ofSetColor(ofColor::blue);
		ofDrawLine(this->entity->transform.Position(), this->entity->transform.Position() + glm::vec3(0, -1, 0) * 100 * this->entity->transform.Scale().x);
		ofSetColor(ofColor::red);
		ofDrawLine(this->entity->transform.Position(), this->entity->transform.Position() + glm::vec3(1, 0, 0) * 100 * this->entity->transform.Scale().y);
	}
}