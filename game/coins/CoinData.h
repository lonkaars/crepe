#pragma once

#include "types.h"
#include <string>

struct CoinData{
	crepe::vec2 start_location = {0,0};
	std::string name = "";
	bool active = false;
	CoinData(crepe::vec2 start_location) : start_location(start_location),name(""), active(false) {}
};
