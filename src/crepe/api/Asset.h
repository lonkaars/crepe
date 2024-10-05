#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace crepe::api {

class Asset {
public:
	Asset(const std::string & src);

public:
	//! Get an input stream to the contents of this resource
	const std::istream & read();
	//! Get the canonical path to this resource
	const char * canonical();

private:
	std::string src;
	std::ifstream file;
};

} // namespace crepe::api
