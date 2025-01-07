#pragma once

#include <vector>

#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>

#include "ZapperObject.h"

class ZapperPoolSubScene {
public:
	ZapperPoolSubScene(crepe::Scene & scene);

public:
	crepe::GameObject controller;
	std::vector<ZapperObject> zappers;

private:
	static constexpr size_t POOL_SIZE = 4;

};
