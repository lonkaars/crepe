#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace crepe::api {

class Resource {
public:
	Resource(const std::string & src);

public:
	const std::istream & read();

private:
	std::string src;
	std::ifstream file;
};

}

