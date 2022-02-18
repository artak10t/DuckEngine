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
	gui.add(isActive.setup("IsActive", entity->isActive));

	position.setName("Position");
	position.add(positionX.set("X", entity->transform.Position().x));
	position.add(positionY.set("Y", entity->transform.Position().y));
	position.add(positionZ.set("Z", entity->transform.Position().z));
	gui.add(position);
}

void Inspector::Draw() {
	if (this->entity == NULL)
		return;

	gui.draw();
}