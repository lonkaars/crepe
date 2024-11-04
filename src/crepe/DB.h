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

class DB {
public:
	DB(const std::string & path);
	virtual ~DB() = default;

public:
	std::string get(const std::string & key);
	void set(const std::string & key, const std::string & value);
	bool has(const std::string & key) noexcept;

private:
	std::unique_ptr<libdb::DB, std::function<void(libdb::DB *)>> db;
	std::unique_ptr<libdb::DBC, std::function<void(libdb::DBC *)>> cursor;

private:
	libdb::DBT to_thing(const std::string & thing) const;
};

}

