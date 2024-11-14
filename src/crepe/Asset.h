#pragma once

#include <string>

namespace crepe {

/**
 * \brief Asset location helper
 *
 * This class is used to locate game asset files, and should *always* be used
 * instead of reading file paths directly.
 */
class Asset {
public:
	/**
	 * \param src  Unique identifier to asset
	 */
	Asset(const std::string & src);
	/**
	 * \param src  Unique identifier to asset
	 */
	Asset(const char * src);

public:
	/**
	 * \brief Get the path to this asset
	 * \return path to this asset
	 */
	const std::string & get_path() const noexcept;

private:
	//! path to asset
	const std::string src;

private:
	std::string find_asset(const std::string & src) const;
	/**
	 * \returns The path to the current executable
	 */
	std::string whereami() const noexcept;
};

} // namespace crepe
