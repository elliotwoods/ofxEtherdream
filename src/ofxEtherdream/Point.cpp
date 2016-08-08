#include "Point.h"

#define SCALE_16 (float)((1 << 15) - 1)

namespace ofxEtherdream {

	//----------
	Point::Point() {
		//default point is white at 0,0
		this->x = 0;
		this->y = 0;
		this->r = 0xFFFF;
		this->g = 0xFFFF;
		this->b = 0xFFFF;
		this->i = 0xFFFF;
		this->u1 = 0;
		this->u2 = 0;
	}

	//----------
	void Point::setNormalized(const ofVec2f & xy) {
		this->x = xy.x * SCALE_16;
		this->y = xy.y * SCALE_16;
	}

	//----------
	void Point::setNormalized(float x, float y) {
		this->setNormalized(ofVec2f(x, y));
	}

	//----------
	ofVec2f Point::getNormalized() const {
		return ofVec2f((float) this->x / SCALE_16
			, (float) this->y / SCALE_16);
	}

	//----------
	void Point::setColor(const ofColor & color) {
		this->r = color.r << 8;
		this->g = color.g << 8;
		this->b = color.b << 8;
		this->i = color.a << 8;
	}

	//----------
	ofColor Point::getColor() const {
		return ofColor(
			this->r >> 8
			, this->g >> 8
			, this->b >> 8
			, this->i >> 8
			);
	}
}