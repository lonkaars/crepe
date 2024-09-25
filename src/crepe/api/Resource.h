#pragma once

#include <string>

namespace crepe::api {

class Resource {
public:
	Resource(const std::string & source);
	virtual ~Resource();

private:
	std::string _source;
};

}

