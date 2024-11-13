#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace crepe {

/**
 * \brief Asset location helper
 *
 * This class is used to locate and canonicalize paths to game asset files, and
 * should *always* be used when retrieving files from disk.
 */
class Asset {
public:
	/**
	 * \param src  Unique identifier to asset
	 */
	Asset(const std::string & src);

public:
	//! Get an input stream to the contents of this resource
	const std::istream & read();
	//! Get the canonical path to this resource
	const char * canonical() const;

private:
	std::string src;
	std::ifstream file;
};

} // namespace crepe
