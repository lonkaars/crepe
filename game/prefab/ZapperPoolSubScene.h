#pragma once

#include <vector>

#include <crepe/api/Scene.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Event.h>
#include <crepe/util/OptionalRef.h>

#include "ZapperObject.h"

class CreateZapperEvent : public crepe::Event {};

class ZapperPoolSubScene {
public:
	ZapperPoolSubScene(crepe::Scene & scene);

private:
	crepe::GameObject controller;
	std::vector<ZapperObject> zappers;

private:
	static constexpr size_t POOL_SIZE = 4;

public:
	crepe::OptionalRef<ZapperObject> get_next_zapper();
};
