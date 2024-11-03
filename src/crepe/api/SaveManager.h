#pragma once

#include <memory>

#include "../ValueBroker.h"

namespace crepe {
class DB;
}

namespace crepe::api {

class SaveManager {
public:
	//! Get a reference to a value and initialize it with a value if it does not yet exist
	template <typename T>
	ValueBroker<T> get(const std::string & key, const T & default_value);

	//! Get a reference to a value
	template <typename T>
	ValueBroker<T> get(const std::string & key);

	//! Set a value directly
	template <typename T>
	void set(const std::string & key, const T & value);

	//! Check if the save file has a value for this \c key
	bool has(const std::string & key);

private:
	SaveManager();
	virtual ~SaveManager() = default;

private:
	template <typename T>
	std::string serialize(const T &);

	template <typename T>
	T deserialize(const std::string &);

public:
	// singleton
	static SaveManager & get_instance();
	SaveManager(const SaveManager &) = delete;
	SaveManager(SaveManager &&) = delete;
	SaveManager & operator = (const SaveManager &) = delete;
	SaveManager & operator = (SaveManager &&) = delete;

private:
	static DB & get_db();
};

}

