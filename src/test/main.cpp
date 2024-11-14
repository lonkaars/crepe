#include <crepe/api/Config.h>

#include <gtest/gtest.h>

using namespace crepe;
using namespace testing;

class GlobalConfigReset : public EmptyTestEventListener {
public:
	Config & cfg = Config::get_instance();

	// This function is called before each test
	void OnTestStart(const TestInfo &) override {
		cfg.log.level = Log::Level::WARNING;
	}
};

int main(int argc, char ** argv) {
	InitGoogleTest(&argc, argv);

	UnitTest & ut = *UnitTest::GetInstance();
	ut.listeners().Append(new GlobalConfigReset);

	return RUN_ALL_TESTS();
}

