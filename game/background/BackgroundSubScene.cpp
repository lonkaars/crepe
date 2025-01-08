#include "BackgroundSubScene.h"
#include "AquariumScript.h"
#include "AquariumSubScene.h"
#include "ForestSubScene.h"
#include "HallwayScript.h"
#include "HallwaySubScene.h"
#include "StartSubScene.h"

#include <crepe/api/BehaviorScript.h>
#include <crepe/api/Color.h>
#include <crepe/api/Scene.h>

using namespace crepe;
using namespace std;

BackgroundSubScene::BackgroundSubScene(Scene & scn) {
	StartSubScene start;
	HallwaySubScene hallway;
	ForestSubScene forest;
	AquariumSubScene aquarium;

	float begin_x = 400;

	begin_x = start.create(scn, begin_x);

	begin_x = hallway.create(scn, begin_x, 1, Color::YELLOW);

	begin_x = forest.create(scn, begin_x, "1");

	begin_x += 3000;

	begin_x = aquarium.create(scn, begin_x);

	GameObject scripts = scn.new_object("scrips_background", "background");
	scripts.add_component<BehaviorScript>().set_script<HallwayScript>();
	scripts.add_component<BehaviorScript>().set_script<AquariumScript>();
}
