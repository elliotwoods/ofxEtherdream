#pragma once

#include "ofMain.h"
#include "ofxEtherdream.h"
#include "ofxCvGui.h"

struct DeviceConnection {
	ofxEtherdream::Device device;
	ofxEtherdream::Frame frame;
	weak_ptr<ofxCvGui::Panels::Base> panel;
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void refreshDevices();
		void openDevice(ofxEtherdream::Device device);
		void closeDevice(ofxEtherdream::Device device);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxCvGui::Builder gui;
		shared_ptr<ofxCvGui::Panels::Widgets> deviceListPanel;

		vector<shared_ptr<DeviceConnection>> deviceConnections;
};
