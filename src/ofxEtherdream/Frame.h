#pragma once

#include "Point.h"
#include "ofBaseTypes.h"

namespace ofxEtherdream {
	class Frame : public ofBaseDraws {
	public:
		//set points to vector<Point> or other STL container
		template<typename Container>
		void setPoints(const Container & points) {
			this->points.clear();
			this->points.insert(points.begin(), points.end());
		}

		const vector<Point> & getPoints() const;
		vector<Point> & getPoints();

		void setPointsPerSecond(uint32_t);
		uint32_t getPointPerSecond() const;

		//--
		//ofBaseDraws
		//--
		//
		void draw(float x, float y, float w, float h) const override;
		void draw(const ofRectangle & rect) const override {
			ofBaseDraws::draw(rect);
		}
		float getHeight() const override;
		float getWidth() const override;
		//
		//--

	protected:
		vector<Point> points;
		uint32_t pointsPerSecond = 30000;
	};
}