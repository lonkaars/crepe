#pragma once

#include <crepe/api/Event.h>
#include <crepe/api/Script.h>
#include <crepe/manager/SaveManager.h>

struct GetCoinEvent : public crepe::Event {
	int amount_of_coins;
};

class HudScript : public crepe::Script {
public:
	void init() override;
	void frame_update(crepe::duration_t dt) override;
	bool get_coin(const GetCoinEvent e);
	bool toggle_fps(crepe::KeyPressEvent ev);
	bool save();

private:
	crepe::SaveManager * savemgr;
	bool show_fps = false;
	int coin_amount = 0;
	std::string coin_amount_st = "";
	std::string distance_st = "";
};
