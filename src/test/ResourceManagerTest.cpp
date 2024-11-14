#include <gtest/gtest.h>

#include <crepe/util/Log.h>
#include <crepe/api/Config.h>
#include <crepe/api/ResourceManager.h>

using namespace std;
using namespace crepe;
using namespace testing;

class ResourceManagerTest : public Test {
public:
	ResourceManager & resman = ResourceManager::get_instance();
	Config & cfg = Config::get_instance();

	void SetUp() override {
		cfg.log.level = Log::Level::TRACE;
		resman.clear();
	}
};

TEST_F(ResourceManagerTest, Main) {
	Asset path1 = "mwe/audio/sfx1.wav";
	Asset path2 = "mwe/audio/sfx1.wav";
	ASSERT_EQ(path1, path2);

	Sound * ptr1 = nullptr;
	Sound * ptr2 = nullptr;
	{
		Log::logf(Log::Level::DEBUG, "Get first sound (constructor call)");
		Sound & sound = resman.cache<Sound>(path1);
		ptr1 = &sound;
	}
	{
		Log::logf(Log::Level::DEBUG, "Get same sound (NO constructor call)");
		Sound & sound = resman.cache<Sound>(path2);
		ptr2 = &sound;
	}
	EXPECT_EQ(ptr1, ptr2);

	Log::logf(Log::Level::DEBUG, "Clear cache (destructor call)");
	resman.clear();

	Log::logf(Log::Level::DEBUG, "Get first sound again (constructor call)");
	Sound & sound = resman.cache<Sound>(path1);

	// NOTE: there is no way (that I know of) to ensure the above statement
	// allocates the new Sound instance in a different location than the first,
	// so this test was verified using the above print statements.
}

