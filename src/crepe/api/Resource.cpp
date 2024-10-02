#include <filesystem>
#include <iostream>
#include <iterator>

#include "Resource.h"
#include "util/log.h"

using namespace crepe::api;

Resource::Resource(const std::string & src) {
	dbg_trace();
	this->src = std::filesystem::path(src);
	this->file = std::ifstream(this->src, std::ios::in | std::ios::binary);
}

const std::istream & Resource::read() { return this->file; }

const char * Resource::canonical() { return this->src.c_str(); }
