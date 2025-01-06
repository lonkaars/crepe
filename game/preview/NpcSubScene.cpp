

#include "NpcSubScene.h"

#include <crepe/api/Scene.h>
#include <crepe/manager/SaveManager.h>
#include <crepe/ValueBroker.h>

using namespace crepe;

NpcSubScene::NpcSubScene(Scene & scn) {
	auto & savemgr = scn.get_save_manager();
	ValueBroker npc_x = savemgr.get<float>("npc_x", -750);
	ValueBroker npc_y = savemgr.get<float>("npc_y", 0);

	GameObject npc = scn.new_object("npc", "npc_tag", vec2 {npc_x.get(), npc_y.get()}, 0, 1);
	Asset npc_body {"asset/workers/worker1Body.png"};
	Asset npc_head {"asset/workers/worker1Head.png"};

}
