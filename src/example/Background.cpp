#include "Background.h"
#include "Aquarium.h"
#include "Forest.h"
#include "Hallway.h"
#include "Start.h"

#include <crepe/api/Color.h>

using namespace crepe;
using namespace std;

Background::Background(Scene & scn) {
	Start start;
	Hallway hallway;
	Forest forest;
	Aquarium aquarium;

	float begin_x = 0;

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
