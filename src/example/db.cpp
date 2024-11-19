#include <crepe/api/Config.h>
#include <crepe/facade/DB.h>
#include <crepe/util/Log.h>

using namespace crepe;
using namespace std;

// run before main
static auto _ = []() {
	auto & cfg = Config::get_instance();
	cfg.log.level = Log::Level::TRACE;
	return 0;
}();

int main() {
	dbg_trace();

	DB db("file.db");

	const char * test_key = "test-key";
	string test_data = "Hello world!";

	dbg_logf("DB has key = {}", db.has(test_key));

	db.set(test_key, test_data);

	dbg_logf("key = \"{}\"", db.get(test_key));

	return 0;
}
