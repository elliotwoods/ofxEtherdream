#include "ofApp.h"
#include <WinSock2.h>

//--------------------------------------------------------------
void ofApp::setup() {
	this->gui.init();
	this->deviceListPanel = this->gui.addWidgets();
	this->refreshDevices();
}

//--------------------------------------------------------------
void ofApp::update(){
	for (auto deviceConnection : this->deviceConnections) {
		deviceConnection->device.sendFrame(deviceConnection->frame);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::refreshDevices() {
	this->deviceListPanel->clear();
	
	this->deviceListPanel->addTitle("ofxEtherdream example");
	this->deviceListPanel->addFps();
	this->deviceListPanel->addMemoryUsage();

	this->deviceListPanel->addButton("Refresh devices", [this]() {
		this->refreshDevices();
	})->setHeight(100);

	this->deviceListPanel->addSpacer();

	//add a toggle for each found device
	{
		auto devices = ofxEtherdream::listDevices();
		for (const auto device : devices) {
			this->deviceListPanel->addToggle(device.getIpAddress(),

				//get function (is the device already in deviceConnections)
				[this, device]() {
					for (auto & deviceConnection : this->deviceConnections) {
						if (deviceConnection->device == device) {
							return true;
						}
						else {
							return false;
						}
					}
				},
				
				//set function
				[this, device](bool toggleState) {
					if (toggleState) {
						this->openDevice(device);
					} else {
						this->closeDevice(device);
					}
				}
			);
		}
	}
}

//----------
void ofApp::openDevice(ofxEtherdream::Device device) {
	device.connect();

	auto deviceConnection = shared_ptr<DeviceConnection>(new DeviceConnection{
		device
	});
	this->deviceConnections.push_back(deviceConnection);

	//create the gui panel
	{
		auto panel = ofxCvGui::Panels::makeBlank();
		deviceConnection->panel = panel;
		panel->onDraw += [deviceConnection](ofxCvGui::DrawArguments & args) {
			//draw the crosshair and grid
			ofPushStyle();
			{
				ofSetLineWidth(1.0f);
				ofSetColor(100);
				ofPushMatrix();
				{
					ofTranslate(args.localBounds.getCenter());
					ofLine(-5, 0, +5, 0);
					ofLine(0, -5, 0, +5);

					ofScale(args.localBounds.width / 2.0f, args.localBounds.height / 2.0f);
					ofRotate(90, 0, +1, 0);
					ofDrawGridPlane(1 / 4.0f, 4, true);
				}
				ofPopMatrix();
			}
			ofPopStyle();

			//draw a grid

			//draw the status
			{
				auto device = deviceConnection->device;
				stringstream status;
				status << "Device ID: " << device.getID() << endl;
				status << device.getIpAddress() << endl;

				status << "Connected : " << (device.isConnected() ? "YES" : "NO") << endl;
				status << "Ready : " << (device.isReady() ? "YES" : "NO") << endl;
				status << "Point count : " << deviceConnection->frame.getPoints().size() << endl;

				ofDrawBitmapString(status.str(), 20, 30);
			}

			//draw the line{
			deviceConnection->frame.draw(args.localBounds);
		};
		panel->onMouse += [deviceConnection](ofxCvGui::MouseArguments & args) {
			auto panel = deviceConnection->panel.lock();
			if (args.takeMousePress(panel) || args.isDragging(panel)) {
				if (args.button == 0) {
					auto xy = args.localNormalized;
					xy -= 0.5f;
					xy *= 2.0f;
					xy.y *= -1.0f;

					ofxEtherdream::Point point;
					point.setNormalized(xy);

					deviceConnection->frame.getPoints().push_back(point);
				}
				else if (args.button == 2) {
					deviceConnection->frame.getPoints().clear();
				}
			}
		};
		this->gui.add(panel);
	}
}

//----------
void ofApp::closeDevice(ofxEtherdream::Device device) {
	for (auto it = this->deviceConnections.begin(); it != this->deviceConnections.end(); ) {
		auto deviceConnection = *it;
		if (deviceConnection->device == device) {
			device.disconnect();
			gui.remove(deviceConnection->panel.lock());
			it = this->deviceConnections.erase(it);
		}
		else {
			it++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
