#pragma once

#include <crepe/api/Event.h>
#include <crepe/api/GameObject.h>
#include <crepe/api/Scene.h>
#include <crepe/util/OptionalRef.h>

class CreateZapperEvent : public crepe::Event {};

class ZapperPoolSubScene {
public:
	ZapperPoolSubScene(crepe::Scene & scene);

private:
	crepe::GameObject controller;

private:
	static constexpr size_t POOL_SIZE = 4;
};
