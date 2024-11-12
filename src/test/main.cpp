#include <crepe/api/Config.h>

#include <gtest/gtest.h>

using namespace crepe;
using namespace testing;

int main(int argc, char **argv) {
  InitGoogleTest(&argc, argv);

	auto & cfg = Config::get_instance();
	cfg.log.level = LogLevel::ERROR;

  return RUN_ALL_TESTS();
}
