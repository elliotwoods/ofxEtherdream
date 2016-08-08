#pragma once

#include "etherdream.h"
#include "ofTypes.h"

namespace ofxEtherdream {
	class Point : public etherdream_point {
	public:
		Point();

		void setNormalized(const ofVec2f &);
		void setNormalized(float x, float y);
		ofVec2f getNormalized() const;

		void setColor(const ofColor &);
		ofColor getColor() const;
	};
};