#include "Initializer.h"
#include "etherdream.h"
#include <memory>

namespace ofxEtherdream {
	//----------
	Initializer & Initializer::X() {
		static auto instance = std::make_unique<Initializer>();
		return *instance;
	}

	//----------
	Initializer::Initializer() {
		etherdream_lib_start();
	}
}