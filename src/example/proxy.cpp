/** \file
 * 
 * Standalone example for usage of the proxy type
 */

#include <crepe/api/Config.h>
#include <crepe/util/log.h>
#include <crepe/Proxy.h>

using namespace std;
using namespace crepe;
using namespace crepe::util;

template <typename T>
class MyProxyHandler : public ProxyHandler<T> {
public:
	virtual void set(const T & val) {
		dbg_logf("set %s", to_string(val).c_str());
		this->val = val;
	}

	virtual const T & get() {
		dbg_logf("get %s", to_string(this->val).c_str());
		return this->val;
	}

private:
	T val = 0;
};

void test_ro(const int & val) { }
void test_rw(int & val) { }

int main() {
	auto & cfg = api::Config::get_instance();
	cfg.log.level = util::LogLevel::DEBUG;

	Proxy<int> val(make_unique<MyProxyHandler<int>>());

	val = 54;

	test_ro(val); // this is allowed
	// test_rw(val); // this should throw a compile error

	return 0;
}

