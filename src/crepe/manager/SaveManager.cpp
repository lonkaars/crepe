#include "../facade/DB.h"
#include "../util/Log.h"
#include "../api/Config.h"
#include "../ValueBroker.h"

#include "SaveManager.h"

using namespace std;
using namespace crepe;

template <>
string SaveManager::serialize(const string & value) const noexcept {
	return value;
}
template <typename T>
string SaveManager::serialize(const T & value) const noexcept {
	return to_string(value);
}
template string SaveManager::serialize(const uint8_t &) const noexcept;
template string SaveManager::serialize(const int8_t &) const noexcept;
template string SaveManager::serialize(const uint16_t &) const noexcept;
template string SaveManager::serialize(const int16_t &) const noexcept;
template string SaveManager::serialize(const uint32_t &) const noexcept;
template string SaveManager::serialize(const int32_t &) const noexcept;
template string SaveManager::serialize(const uint64_t &) const noexcept;
template string SaveManager::serialize(const int64_t &) const noexcept;
template string SaveManager::serialize(const float &) const noexcept;
template string SaveManager::serialize(const double &) const noexcept;

template <>
uint64_t SaveManager::deserialize(const string & value) const noexcept {
	try {
		return stoul(value);
	} catch (std::invalid_argument &) {
		return 0;
	}
}
template <>
int64_t SaveManager::deserialize(const string & value) const noexcept {
	try {
		return stol(value);
	} catch (std::invalid_argument &) {
		return 0;
	}
}
template <>
float SaveManager::deserialize(const string & value) const noexcept {
	try {
		return stof(value);
	} catch (std::invalid_argument &) {
		return 0;
	}
	return stof(value);
}
template <>
double SaveManager::deserialize(const string & value) const noexcept {
	try {
		return stod(value);
	} catch (std::invalid_argument &) {
		return 0;
	}
}
template <>
string SaveManager::deserialize(const string & value) const noexcept {
	return value;
}

template <>
uint8_t SaveManager::deserialize(const string & value) const noexcept {
	return deserialize<uint64_t>(value);
}
template <>
int8_t SaveManager::deserialize(const string & value) const noexcept {
	return deserialize<int64_t>(value);
}
template <>
uint16_t SaveManager::deserialize(const string & value) const noexcept {
	return deserialize<uint64_t>(value);
}
template <>
int16_t SaveManager::deserialize(const string & value) const noexcept {
	return deserialize<int64_t>(value);
}
template <>
uint32_t SaveManager::deserialize(const string & value) const noexcept {
	return deserialize<uint64_t>(value);
}
template <>
int32_t SaveManager::deserialize(const string & value) const noexcept {
	return deserialize<int64_t>(value);
}

SaveManager::SaveManager() { dbg_trace(); }

SaveManager & SaveManager::get_instance() {
	dbg_trace();
	static SaveManager instance;
	return instance;
}

DB & SaveManager::get_db() {
	Config & cfg = Config::get_instance();
	// TODO: make this path relative to XDG_DATA_HOME on Linux and whatever the
	// default equivalent is on Windows using some third party library
	static DB db(cfg.savemgr.location);
	return db;
}

bool SaveManager::has(const string & key) {
	DB & db = this->get_db();
	return db.has(key);
}

template <>
void SaveManager::set(const string & key, const string & value) {
	DB & db = this->get_db();
	db.set(key, value);
}
template <typename T>
void SaveManager::set(const string & key, const T & value) {
	DB & db = this->get_db();
	db.set(key, std::to_string(value));
}
template void SaveManager::set(const string &, const uint8_t &);
template void SaveManager::set(const string &, const int8_t &);
template void SaveManager::set(const string &, const uint16_t &);
template void SaveManager::set(const string &, const int16_t &);
template void SaveManager::set(const string &, const uint32_t &);
template void SaveManager::set(const string &, const int32_t &);
template void SaveManager::set(const string &, const uint64_t &);
template void SaveManager::set(const string &, const int64_t &);
template void SaveManager::set(const string &, const float &);
template void SaveManager::set(const string &, const double &);

template <typename T>
ValueBroker<T> SaveManager::get(const string & key, const T & default_value) {
	if (!this->has(key)) this->set<T>(key, default_value);
	return this->get<T>(key);
}
template ValueBroker<uint8_t> SaveManager::get(const string &, const uint8_t &);
template ValueBroker<int8_t> SaveManager::get(const string &, const int8_t &);
template ValueBroker<uint16_t> SaveManager::get(const string &, const uint16_t &);
template ValueBroker<int16_t> SaveManager::get(const string &, const int16_t &);
template ValueBroker<uint32_t> SaveManager::get(const string &, const uint32_t &);
template ValueBroker<int32_t> SaveManager::get(const string &, const int32_t &);
template ValueBroker<uint64_t> SaveManager::get(const string &, const uint64_t &);
template ValueBroker<int64_t> SaveManager::get(const string &, const int64_t &);
template ValueBroker<float> SaveManager::get(const string &, const float &);
template ValueBroker<double> SaveManager::get(const string &, const double &);
template ValueBroker<string> SaveManager::get(const string &, const string &);

template <typename T>
ValueBroker<T> SaveManager::get(const string & key) {
	T value;
	return {
		[this, key](const T & target) { this->set<T>(key, target); },
		[this, key, value]() mutable -> const T & {
			value = this->deserialize<T>(this->get_db().get(key));
			return value;
		},
	};
}
template ValueBroker<uint8_t> SaveManager::get(const string &);
template ValueBroker<int8_t> SaveManager::get(const string &);
template ValueBroker<uint16_t> SaveManager::get(const string &);
template ValueBroker<int16_t> SaveManager::get(const string &);
template ValueBroker<uint32_t> SaveManager::get(const string &);
template ValueBroker<int32_t> SaveManager::get(const string &);
template ValueBroker<uint64_t> SaveManager::get(const string &);
template ValueBroker<int64_t> SaveManager::get(const string &);
template ValueBroker<float> SaveManager::get(const string &);
template ValueBroker<double> SaveManager::get(const string &);
template ValueBroker<string> SaveManager::get(const string &);
