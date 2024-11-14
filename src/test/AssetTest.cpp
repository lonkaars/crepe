#include <gtest/gtest.h>

#include <crepe/api/Asset.h>
#include <crepe/api/Config.h>

using namespace std;
using namespace crepe;
using namespace testing;

class AssetTest : public Test {
public:
	Config & cfg = Config::get_instance();
	void SetUp() override {
		this->cfg.asset.root_pattern = ".crepe-root";
	}
};

TEST_F(AssetTest, Existant) {
	ASSERT_NO_THROW(Asset{"asset/texture/img.png"});
}

TEST_F(AssetTest, Nonexistant) {
	ASSERT_ANY_THROW(Asset{"asset/nonexistant"});
}

TEST_F(AssetTest, Rootless) {
	cfg.asset.root_pattern.clear();

	string arbitrary = "\\/this is / /../passed through as-is";
	Asset asset{arbitrary};
	ASSERT_EQ(arbitrary, asset.get_path());
}

