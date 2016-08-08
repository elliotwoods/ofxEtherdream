#include "ofxEtherdream.h"

namespace ofxEtherdream {
	//----------
	std::vector<Device> listDevices() {
		Initializer::X();

		std::vector<Device> devices;

		auto deviceCount = etherdream_dac_count();
		for (int i = 0; i < deviceCount; i++) {
			devices.emplace_back(etherdream_get(i));
		}

		return devices;
	}
}
