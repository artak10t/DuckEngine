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
		void DrawSpaceAxis();

		Entity* entity;
		ofxPanel gui;
		ofxToggle localSpace;
		ofxToggle isActive;
		ofParameterGroup position;
		ofParameter<float> positionX;
		ofParameter<float> positionY;
		ofParameter<float> positionZ;
};