#include "Frame.h"
#include "ofGraphics.h"

namespace ofxEtherdream {
	//----------
	const vector<Point> & Frame::getPoints() const {
		return this->points;
	}

	//----------
	vector<Point> & Frame::getPoints() {
		return this->points;
	}

	//----------
	void Frame::setPointsPerSecond(uint32_t pointsPerSecond) {
		this->pointsPerSecond = pointsPerSecond;
	}

	//----------
	uint32_t Frame::getPointPerSecond() const {
		return this->pointsPerSecond;
	}

	//----------
	void Frame::draw(float x, float y, float w, float h) const {
		ofPushMatrix();
		{
			ofTranslate(x, y);
			ofScale(w / 2.0f, -h / 2.0f);
			ofTranslate(1.0f, -1.0f);

			ofMesh lines;
			lines.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINE_STRIP);
			for (const auto & point : this->points) {
				lines.addVertex(point.getNormalized());
				lines.addColor(point.getColor());
			}
			lines.draw();
		}
		ofPopMatrix();
	}

	//----------
	float Frame::getHeight() const {
		return 1.0f;
	}

	//----------
	float Frame::getWidth() const {
		return 1.0f;
	}

}
