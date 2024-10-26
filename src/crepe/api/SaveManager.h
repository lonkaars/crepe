#pragma once

#include "../Proxy.h"

namespace crepe::api {

class SaveManager {
public:
	//! Get a reference to a value and initialize it with a value if it does not yet exist
	template <typename T>
	Proxy<T> & get(const char * key, const T & default_value);

	//! Get a reference to a value
	template <typename T>
	Proxy<T> & get(const char * key);

	//! Set a value directly
	template <typename T>
	void set(const char * key, const T & value);

	//! Check if the save file has a value for this \c key
	bool has(const char * key);

private:
	SaveManager();
	virtual ~SaveManager();

public:
	// singleton
	static SaveManager & get_instance();
	SaveManager(const SaveManager &) = delete;
	SaveManager(SaveManager &&) = delete;
	SaveManager & operator = (const SaveManager &) = delete;
	SaveManager & operator = (SaveManager &&) = delete;
};

}

#include "SaveManager.hpp"
