#include <filesystem>

#include "Asset.h"

using namespace crepe;

Asset::Asset(const std::string & src) {
	//this->src = std::filesystem::canonical(src);
	this->src = src;
	this->file = std::ifstream(this->src, std::ios::in | std::ios::binary);
}

const std::istream & Asset::read() { return this->file; }

const char * Asset::canonical() { return this->src.c_str(); }
