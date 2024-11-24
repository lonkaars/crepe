#include <gtest/gtest.h>

#include <crepe/api/Asset.h>
#include <crepe/api/Config.h>

using namespace std;
using namespace crepe;
using namespace testing;

TEST(AssetTest, Existant) { ASSERT_NO_THROW(Asset{"asset/texture/img.png"}); }

TEST(AssetTest, Nonexistant) { ASSERT_ANY_THROW(Asset{"asset/nonexistant"}); }

TEST(AssetTest, Rootless) {
	Config & cfg = Config::get_instance();
	cfg.asset.root_pattern.clear();

	string arbitrary = "\\/this is / /../passed through as-is";
	Asset asset{arbitrary};
	ASSERT_EQ(arbitrary, asset.get_path());
}
