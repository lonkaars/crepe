#include <filesystem>

#include "Asset.h"

using namespace crepe;
using namespace std;

// FIXME: restore this
// src(std::filesystem::canonical(src))
Asset::Asset(const std::string & src) : src(src) {
	this->file = std::ifstream(this->src, std::ios::in | std::ios::binary);
}

istream & Asset::get_stream() { return this->file; }

const string & Asset::get_canonical() const { return this->src; }
