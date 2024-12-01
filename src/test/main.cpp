#include <gtest/gtest.h>

#define protected public
#define private public

#include <crepe/api/Config.h>

using namespace crepe;
using namespace testing;

class GlobalConfigReset : public EmptyTestEventListener {
public:
	Config & cfg = Config::get_instance();
	Config cfg_default = Config();

	// This function is called before each test
	void OnTestStart(const TestInfo &) override {
		cfg = cfg_default;
		cfg.log.level = Log::Level::WARNING;
	}
};

int main(int argc, char ** argv) {
	InitGoogleTest(&argc, argv);

	UnitTest & ut = *UnitTest::GetInstance();
	ut.listeners().Append(new GlobalConfigReset);

	return RUN_ALL_TESTS();
}
