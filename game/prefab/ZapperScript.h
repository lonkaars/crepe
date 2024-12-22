#pragma once

#include <crepe/api/Script.h>

#include "ZapperObject.h"

class ZapperScript : public crepe::Script {
public:
	ZapperScript(const ZapperObject & zapper);

protected:
	void init();
	void frame_update(crepe::duration_t delta_time);

protected:
	ZapperObject zapper;
};
