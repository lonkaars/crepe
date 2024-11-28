#include <gtest/gtest.h>

// stupid hack to allow access to private/protected members under test
#define private public
#define protected public

#include <crepe/manager/SceneManager.h>
#include "ScriptTest.h"

using namespace std;
using namespace crepe;
using namespace testing;

class ScriptSceneTest : public ScriptTest {
public:
	SceneManager scene_manager{mediator};

	class MyScene : public Scene {};
};

TEST_F(ScriptSceneTest, Inactive) {
	BehaviorScript & behaviorscript = this->behaviorscript;
	MyScript & script = this->script;

	const char * non_default_value = "foo";
	ASSERT_NE(non_default_value, scene_manager.next_scene);

	script.set_next_scene(non_default_value);
	EXPECT_EQ(non_default_value, scene_manager.next_scene);
}

