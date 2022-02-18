#pragma once

#include "ofxGui.h"
#include "../Entity.h"

class Inspector
{
	public:
		void Setup();
		void Inspect(Entity* entity);
		void Draw();

	private:
		Entity* entity;
		ofxPanel gui;
		ofxToggle isActive;
		ofParameterGroup position;
		ofParameter<float> positionX;
		ofParameter<float> positionY;
		ofParameter<float> positionZ;
};