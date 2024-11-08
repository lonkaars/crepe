#pragma once

#include <string>
#include <functional>
#include <memory>

namespace libdb {
extern "C" {
#include <db.h>
}
}

namespace crepe {

/**
 * \brief Berkeley DB facade
 *
 * Berkeley DB is a simple key-value database that stores arbitrary data as
 * both key and value. This facade uses STL strings as keys/values.
 */
class DB {
public:
	/**
	 * \param path  The path of the database (created if nonexistant)
	 */
	DB(const std::string & path);
	virtual ~DB() = default;

public:
	/**
	 * \brief Get a value from the database, or throw an exception
	 *
	 * \param key  The value key
	 *
	 * \return The value
	 *
	 * \throws Exception if value is not found in DB or other error occurs
	 */
	std::string get(const std::string & key);
	/**
	 * \brief Set (create or overwrite) a value in the database
	 *
	 * \param key  The value key
	 * \param value  The value to store
	 *
	 * \throws Exception if an error occurs
	 */
	void set(const std::string & key, const std::string & value);
	/**
	 * \brief Check if a key exists in the database
	 *
	 * \param key  The value key
	 *
	 * \returns True if the key exists, or false if it does not
	 */
	bool has(const std::string & key) noexcept;

private:
	//! RAII wrapper around \c DB struct
	std::unique_ptr<libdb::DB, std::function<void(libdb::DB *)>> db;
	//! RAII wrapper around \c DBC struct
	std::unique_ptr<libdb::DBC, std::function<void(libdb::DBC *)>> cursor;

private:
	/**
	 * \brief Convert an STL string to DBT (data base thang)
	 *
	 * \param thing  Input data
	 * \return \c DBT with the same data as input \c thing
	 */
	libdb::DBT to_thing(const std::string & thing) const noexcept;
};

}

