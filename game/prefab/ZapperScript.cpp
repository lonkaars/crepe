#include <cassert>
#include <crepe/api/Rigidbody.h>

#include "ZapperScript.h"

using namespace crepe;
using namespace std;

ZapperScript::ZapperScript(const ZapperObject & zapper) : zapper(zapper) {}

void ZapperScript::init() {
	zapper.sprite.beam.mask = {
		.w = 350,
		.h = 117,
		.x = 0,
		.y = 0,
	};
}

void ZapperScript::frame_update(duration_t delta_time) { zapper.sprite.beam.mask.x += 4; }
