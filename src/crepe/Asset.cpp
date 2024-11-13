#include <filesystem>

#include "Asset.h"
#include "Exception.h"

using namespace crepe;
using namespace std;

Asset::Asset(const string & src) : src(src) {
	try {
		this->src = filesystem::canonical(src);
	} catch (filesystem::filesystem_error & e) {
		throw Exception("Asset error: %s", e.what());
	}
	this->file = ifstream(this->src, ios::in | ios::binary);
}

const istream & Asset::read() { return this->file; }

const char * Asset::canonical() const { return this->src.c_str(); }
