#include "Background.h"
#include "Aquarium.h"
#include "Forest.h"
#include "Hallway.h"
#include "Start.h"

#include <crepe/api/Animator.h>
#include <crepe/api/Asset.h>
#include <crepe/api/BehaviorScript.h>
#include <crepe/api/BoxCollider.h>
#include <crepe/api/Camera.h>
#include <crepe/api/CircleCollider.h>
#include <crepe/api/Color.h>
#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/LoopManager.h>
#include <crepe/api/Rigidbody.h>
#include <crepe/api/Scene.h>
#include <crepe/api/Script.h>
#include <crepe/api/Sprite.h>
#include <crepe/api/Transform.h>
#include <crepe/api/Vector2.h>
#include <crepe/types.h>
#include <iostream>

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
