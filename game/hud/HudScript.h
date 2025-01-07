#pragma once

#include "api/Event.h"
#include "api/Script.h"
#include "manager/SaveManager.h"

struct GetCoinEvent : public crepe::Event {
	int amount_of_coins;
};

class HudScript : public crepe::Script {
public:
	void init() override;
	void frame_update(crepe::duration_t dt) override;
	bool get_coin(const GetCoinEvent e);
	bool toggle_fps(crepe::KeyPressEvent ev);
private:
	crepe::SaveManager* savemgr;
	bool show_fps = false;
	int coin_amount = 0;
};
