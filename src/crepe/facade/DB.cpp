#include <cstring>

#include "Exception.h"
#include "util/log.h"

#include "DB.h"

using namespace std;
using namespace crepe;

DB::DB(const string & path) {
	dbg_trace();
	int ret;

	// init database struct
	libdb::DB * db;
	if ((ret = libdb::db_create(&db, NULL, 0)) != 0)
		throw Exception("db_create: %s", libdb::db_strerror(ret));
	this->db = {db, [](libdb::DB * db) { db->close(db, 0); }};

	// load or create database file
	ret = this->db->open(this->db.get(), NULL, path.c_str(), NULL,
						 libdb::DB_BTREE, DB_CREATE, 0);
	if (ret != 0) throw Exception("db->open: %s", libdb::db_strerror(ret));

	// create cursor
	libdb::DBC * cursor;
	ret = this->db->cursor(this->db.get(), NULL, &cursor, 0);
	if (ret != 0) throw Exception("db->cursor: %s", libdb::db_strerror(ret));
	this->cursor = {cursor, [](libdb::DBC * cursor) { cursor->close(cursor); }};
}

libdb::DBT DB::to_thing(const string & thing) const noexcept {
	libdb::DBT thang;
	memset(&thang, 0, sizeof(libdb::DBT));
	thang.data = (void *) thing.data();
	thang.size = thing.size();
	return thang;
}

string DB::get(const string & key) {
	libdb::DBT db_key = this->to_thing(key);
	libdb::DBT db_val;
	memset(&db_val, 0, sizeof(libdb::DBT));

	int ret = this->cursor->get(this->cursor.get(), &db_key, &db_val, DB_FIRST);
	if (ret != 0) throw Exception("cursor->get: %s", libdb::db_strerror(ret));
	return {static_cast<char *>(db_val.data), db_val.size};
}

void DB::set(const string & key, const string & value) {
	libdb::DBT db_key = this->to_thing(key);
	libdb::DBT db_val = this->to_thing(value);
	int ret = this->db->put(this->db.get(), NULL, &db_key, &db_val, 0);
	if (ret != 0) throw Exception("cursor->get: %s", libdb::db_strerror(ret));
}

bool DB::has(const std::string & key) noexcept {
	try {
		this->get(key);
	} catch (...) {
		return false;
	}
	return true;
}
