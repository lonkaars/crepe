#pragma once

#include <memory>
#include <functional>

#include "../ValueBroker.h"

#include "Manager.h"

namespace crepe {

class DB;

/**
 * \brief Save data manager
 *
 * This class provides access to a simple key-value store that stores
 * - integers (8-64 bit, signed or unsigned)
 * - real numbers (float or double)
 * - string (std::string)
 *
 * The underlying database is a key-value store.
 */
class SaveManager : public Manager {
public:
	/**
	 * \brief Get a read/write reference to a value and initialize it if it does not yet exist
	 *
	 * \param key  The value key
	 * \param default_value  Value to initialize \c key with if it does not already exist in the
	 * database
	 *
	 * \return Read/write reference to the value
	 */
	template <typename T>
	ValueBroker<T> get(const std::string & key, const T & default_value);

	/**
	 * \brief Get a read/write reference to a value
	 *
	 * \param key  The value key
	 *
	 * \return Read/write reference to the value
	 *
	 * \note Attempting to read this value before it is initialized (i.e. set) will result in an
	 * exception
	 */
	template <typename T>
	ValueBroker<T> get(const std::string & key);

	/**
	 * \brief Set a value directly
	 *
	 * \param key  The value key
	 * \param value  The value to store
	 */
	template <typename T>
	void set(const std::string & key, const T & value);

	/**
	 * \brief Check if the save file has a value for this \c key
	 *
	 * \param key  The value key
	 *
	 * \returns True if the key exists, or false if it does not
	 */
	bool has(const std::string & key);

public:
	SaveManager(Mediator & mediator);
	virtual ~SaveManager() = default;

private:
	/**
	 * \brief Serialize an arbitrary value to STL string
	 *
	 * \tparam T  Type of arbitrary value
	 *
	 * \returns String representation of value
	 */
	template <typename T>
	std::string serialize(const T &) const noexcept;

	/**
	 * \brief Deserialize an STL string back to type \c T
	 *
	 * \tparam T  Type of value
	 * \param value  Serialized value
	 *
	 * \returns Deserialized value
	 */
	template <typename T>
	T deserialize(const std::string & value) const noexcept;

protected:
	//! Create or return DB
	virtual DB & get_db();
private:
	//! Database
	std::unique_ptr<void, std::function<void(void*)>> db = nullptr;
};

} // namespace crepe
