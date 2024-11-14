#include <gtest/gtest.h>

#include <crepe/api/ResourceManager.h>

using namespace std;
using namespace crepe;
using namespace testing;

class ResourceManagerTest : public Test {
public:
	ResourceManager & manager = ResourceManager::get_instance();

	void SetUp() override {
		this->manager.clear();
	}
};

TEST_F(ResourceManagerTest, Main) {
	Sound & sound = this->manager.cache<Sound>("mwe/audio/sfx1.wav");
}

