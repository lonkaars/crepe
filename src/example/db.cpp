#include <crepe/DB.h>
#include <crepe/api/Config.h>
#include <crepe/util/log.h>

using namespace crepe;
using namespace std;

// run before main
static auto _ = [] () {
	auto & cfg = api::Config::get_instance();
	cfg.log.level = util::LogLevel::TRACE;
	return 0;
}();

int main() {
	dbg_trace();

	DB db("file.db");

	const char * test_key = "test-key";
	string test_data = "Hello world!";

	dbg_logf("DB has key = %d", db.has(test_key));

	db.set(test_key, test_data);

	dbg_logf("key = \"%s\"", db.get(test_key).c_str());

	return 0;
}
