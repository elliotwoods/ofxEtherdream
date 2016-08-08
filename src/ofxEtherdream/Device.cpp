#include "Device.h"

#include <sstream>
#include <iostream>

#ifdef _MSC_VER
	#include <WinSock2.h>
#endif

using namespace std;

namespace ofxEtherdream {
	//----------
	Device::Device(etherdream * rawDevice)
		: rawDevice(rawDevice) {
	}

	//----------
	uint32_t Device::getID() const {
		return etherdream_get_id(this->rawDevice);
	}

	//----------
	const std::string Device::getIpAddress() const {
		auto address = etherdream_get_in_addr(this->rawDevice);

		std::stringstream ipAddressStream;

		ipAddressStream << (int)address->S_un.S_un_b.s_b1
			<< "." << (int)address->S_un.S_un_b.s_b2
			<< "." << (int)address->S_un.S_un_b.s_b3
			<< "." << (int)address->S_un.S_un_b.s_b4;

		return ipAddressStream.str();
	}

	//----------
	void Device::connect() {
		etherdream_connect(this->rawDevice);
	}

	//----------
	void Device::disconnect() {
		if(this->isConnected()) {
			etherdream_disconnect(this->rawDevice);
		}
	}

	//----------
	bool Device::isConnected() const {
		return etherdream_is_connected(this->rawDevice);
	}

	//----------
	bool Device::isReady() const {
		if (!this->isConnected()) {
			return false;
		}
		else {
			//will crash if not connected
			return etherdream_is_ready(this->rawDevice);
		}
	}

	//----------
	void Device::waitForReady() {
		etherdream_wait_for_ready(this->rawDevice);
	}

	//----------
	void Device::stop() {
		etherdream_stop(this->rawDevice);
	}

	//----------
	void Device::sendFrame(const Frame & frame, int repetitions /*=-1*/) {
		if (frame.getPoints().empty()) {
			this->stop();
			return;
		}
		etherdream_write(this->rawDevice
			, (etherdream_point *)frame.getPoints().data()
			, frame.getPoints().size()
			, frame.getPointPerSecond()
			, repetitions);
	}

	//----------
	bool Device::operator==(const Device & other) const {
		return this->getRawDevice() == other.getRawDevice();
	}

	//----------
	etherdream * Device::getRawDevice() const {
		return this->rawDevice;
	}
}