#include <filesystem>
#include <stdexcept>
#include <whereami.h>

#include "Asset.h"
#include "api/Config.h"

using namespace crepe;
using namespace std;

Asset::Asset(const string & src) : src(find_asset(src)) { }
Asset::Asset(const char * src) : src(find_asset(src)) { }

const string & Asset::get_path() const noexcept { return this->src; }

string Asset::find_asset(const string & src) const {
	auto & cfg = Config::get_instance();
	auto & root_pattern = cfg.asset.root_pattern;

	// if root_pattern is empty, find_asset must return all paths as-is
	if (root_pattern.empty()) return src;

	// absolute paths do not need to be resolved, only canonicalized
	filesystem::path path = src;
	if (path.is_absolute())
		return filesystem::canonical(path);

	// find directory matching root_pattern
	filesystem::path root = this->whereami();
	while (1) {
		if (filesystem::exists(root / root_pattern))
			break;
		if (!root.has_parent_path())
			throw runtime_error(format("Asset: Cannot find root pattern ({})", root_pattern));
		root = root.parent_path();
	}

	// join path to root (base directory) and canonicalize
	return filesystem::canonical(root / path);
}

string Asset::whereami() const noexcept {
	string path;
	size_t path_length = wai_getExecutablePath(NULL, 0, NULL);
	path.resize(path_length + 1); // wai writes null byte
	wai_getExecutablePath(path.data(), path_length, NULL);
	path.resize(path_length);
	return path;
}

