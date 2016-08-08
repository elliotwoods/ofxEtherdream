#include "ofApp.h"
#include <WinSock2.h>

//--------------------------------------------------------------
void ofApp::setup() {
	etherdream_lib_start();

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	auto deviceCount = etherdream_dac_count();

	stringstream message;
	for (int index = 0; index < deviceCount; index++) {
		auto device = etherdream_get(index);

		auto id = etherdream_get_id(device);
		auto address = etherdream_get_in_addr(device);

		message << "Device #" << index << ": {" << endl;
		message << "\tid=" << id << endl;
		message << "\taddress="
			<< (int) address->S_un.S_un_b.s_b1
			<< "." << (int) address->S_un.S_un_b.s_b2
			<< "." << (int) address->S_un.S_un_b.s_b3
			<< "." << (int) address->S_un.S_un_b.s_b4 << endl;
		message << "}" << endl;

	}
	ofDrawBitmapString(message.str(), 30, 60);
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
