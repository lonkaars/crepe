#include "Resource.h"

using namespace crepe::api;

Resource::Resource(const std::string & src) : src(src) {
	this->file = std::ifstream(src, std::ios::in | std::ios::binary);
}

const std::istream & Resource::read() {
	return this->file;
}

