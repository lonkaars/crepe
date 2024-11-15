#pragma once

#include <fstream>
#include <iostream>
#include <string>

namespace crepe {

/**
 * \brief Asset location helper
 *
 * This class is used to locate and canonicalize paths to game asset files, and should *always*
 * be used when retrieving files from disk.
 */
class Asset {
public:
	/**
	 * \param src  Unique identifier to asset
	 */
	Asset(const std::string & src);

public:
	/**
	 * \brief Get an input stream to the contents of this asset
	 * \return Input stream with file contents
	 */
	std::istream & get_stream();
	/**
	 * \brief Get the canonical path to this asset
	 * \return Canonical path to this asset
	 */
	const std::string & get_canonical() const;

private:
	//! Canonical path to asset
	const std::string src;
	//! File handle (stream)
	std::ifstream file;
};

} // namespace crepe
