#pragma once

#include "Frame.h"
#include "etherdream.h"
#include <string>
#include <stdint.h>

// check etherdream.h for reference of how each function is designed

namespace ofxEtherdream {
	class Device {
	public:
		Device(etherdream * rawDevice);

		uint32_t getID() const;
		const std::string getIpAddress() const;

		void connect();
		void disconnect();
		bool isConnected() const;
		
		bool isReady() const;
		void waitForReady();

		void stop();

		//-1 = repeat until new data arrives
		void sendFrame(const Frame &, int repetitions = -1);

		bool operator==(const Device & other) const;
		etherdream * getRawDevice() const;
	protected:
		etherdream * const rawDevice;
	};
}