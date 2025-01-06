#include "BackgroundSubScene.h"
#include "AquariumSubScene.h"
#include "ForestSubScene.h"
#include "HallwaySubScene.h"
#include "StartSubScene.h"

#include <crepe/api/Color.h>

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

	begin_x = hallway.create(scn, begin_x, 2, Color::MAGENTA);

	begin_x = aquarium.create(scn, begin_x);

	begin_x = hallway.create(scn, begin_x, 3, Color::CYAN);

	begin_x = forest.create(scn, begin_x, "2");

	begin_x = hallway.create(scn, begin_x, 4, Color::GREEN);

	begin_x = aquarium.create(scn, begin_x);
}
