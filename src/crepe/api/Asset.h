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

	/**
	 * \brief Comparison operator
	 * \param other Possibly different instance of \c Asset to test equality against
	 * \return True if \c this and \c other are equal
	 */
	bool operator==(const Asset & other) const noexcept;

private:
	//! path to asset
	const std::string src;

private:
	/**
	 * \brief Locate asset path, or throw exception if it cannot be found
	 *
	 * This function resolves asset locations relative to crepe::Config::root_pattern if it is
	 * set and \p src is a relative path. If \p src is an absolute path, it is canonicalized.
	 * This function only returns if the file can be found.
	 *
	 * \param src Arbitrary path to resource file
	 *
	 * \returns \p src if crepe::Config::root_pattern is empty
	 * \returns Canonical path to \p src
	 *
	 * \throws std::runtime_error if root_pattern cannot be found
	 * \throws std::filesystem::filesystem_error if the resolved path does not exist
	 * \throws std::filesystem::filesystem_error if the path cannot be canonicalized
	 */
	std::string find_asset(const std::string & src) const;
	/**
	 * \returns The path to the current executable
	 */
	std::string whereami() const noexcept;
};

} // namespace crepe

namespace std {

//! Hash helper struct
template <>
struct hash<const crepe::Asset> {
	/**
	 * \brief Hash operator for crepe::Asset
	 *
	 * This function hashes a crepe::Asset instance, allowing it to be used as a key in an \c
	 * std::unordered_map.
	 *
	 * \returns Hash value
	 */
	size_t operator()(const crepe::Asset & asset) const noexcept;
};

} // namespace std
