#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace crepe::api {

class Resource {
public:
	Resource(const std::string & src);

public:
	//! Get an input stream to the contents of this resource
	const std::istream & read();
	//! Get the canonical path to this resource
	const char * canonical();

private:
	std::string src;
	std::ifstream file;
};

}

