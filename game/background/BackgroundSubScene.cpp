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

	begin_x = hallway.create(scn, begin_x, 5, Color::RED);

	begin_x = forest.create(scn, begin_x, "3");

	begin_x = hallway.create(scn, begin_x, 6, Color::BLUE);

	begin_x = aquarium.create(scn, begin_x);

	begin_x = hallway.create(scn, begin_x, 7, Color::WHITE);

	begin_x = forest.create(scn, begin_x, "4");

	begin_x = hallway.create(scn, begin_x, 8, Color::YELLOW);

	begin_x = aquarium.create(scn, begin_x);

	begin_x = hallway.create(scn, begin_x, 9, Color::MAGENTA);

	begin_x = forest.create(scn, begin_x, "5");

	begin_x = hallway.create(scn, begin_x, 10, Color::CYAN);

	begin_x = aquarium.create(scn, begin_x);

	begin_x = hallway.create(scn, begin_x, 11, Color::GREEN);

	begin_x = forest.create(scn, begin_x, "6");

	begin_x = hallway.create(scn, begin_x, 12, Color::RED);

	begin_x = aquarium.create(scn, begin_x);

	begin_x = hallway.create(scn, begin_x, 13, Color::BLUE);

	begin_x = forest.create(scn, begin_x, "7");

	begin_x = hallway.create(scn, begin_x, 14, Color::WHITE);

	begin_x = aquarium.create(scn, begin_x);

	begin_x = hallway.create(scn, begin_x, 15, Color::YELLOW);

	begin_x = forest.create(scn, begin_x, "8");

	begin_x = hallway.create(scn, begin_x, 16, Color::MAGENTA);
}
