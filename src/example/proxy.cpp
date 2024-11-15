/** \file
 * 
 * Standalone example for usage of the proxy type
 */

#include <crepe/ValueBroker.h>
#include <crepe/api/Config.h>
#include <crepe/util/Proxy.h>
#include <crepe/util/log.h>

using namespace std;
using namespace crepe;

void test_ro_ref(const int & val) {}
void test_rw_ref(int & val) {}
void test_ro_val(int val) {}

int main() {
	auto & cfg = Config::get_instance();
	cfg.log.level = LogLevel::DEBUG;

	int real_value = 0;

	ValueBroker<int> broker{
		[&real_value](const int & target) {
			dbg_logf("set %s to %s", to_string(real_value).c_str(), to_string(target).c_str());
			real_value = target;
		},
		[&real_value]() -> const int & {
			dbg_logf("get %s", to_string(real_value).c_str());
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
