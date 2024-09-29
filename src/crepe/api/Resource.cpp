#include <filesystem>

#include "Resource.h"

using namespace crepe::api;

Resource::Resource(const std::string & src) {
	this->src = std::filesystem::canonical(src);
	this->file = std::ifstream(this->src, std::ios::in | std::ios::binary);
}

const std::istream & Resource::read() {
	return this->file;
}

const char * Resource::canonical() {
	return this->src.c_str();
}

