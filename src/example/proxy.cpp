/** \file
 * 
 * Standalone example for usage of the proxy type
 */

#include <crepe/ValueBroker.h>
#include <crepe/api/Config.h>
#include <crepe/util/Log.h>
#include <crepe/util/Proxy.h>

using namespace std;
using namespace crepe;

void test_ro_ref(const int & val) {}
void test_rw_ref(int & val) {}
void test_ro_val(int val) {}

int main() {
	auto & cfg = Config::get_instance();
	cfg.log.level = Log::Level::DEBUG;

	int real_value = 0;

	ValueBroker<int> broker{
		[&real_value](const int & target) {
			dbg_logf("set {} to {}", real_value, target);
			real_value = target;
		},
		[&real_value]() -> const int & {
			dbg_logf("get {}", real_value);
			return real_value;
		},
	};

	Proxy<int> proxy{broker};

	broker.set(54);
	proxy = 84;

	test_ro_ref(proxy); // this is allowed
	// test_rw_ref(proxy); // this should throw a compile error
	test_ro_val(proxy);

	return 0;
}
