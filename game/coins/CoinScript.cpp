#include "CoinScript.h"
#include "api/CircleCollider.h"
#include "api/Sprite.h"
#include "manager/SaveManager.h"
#include "../Config.h"
#include "../Events.h"
#include "../hud/HudScript.h"

using namespace crepe;
using namespace std;

bool CoinScript::on_collision(const CollisionEvent & collisionData){
	if(collisionData.info.other.metadata.tag != "coin") return true;
	this->get_components_by_name<Sprite>(collisionData.info.other.metadata.name).front().get().active = false;
	this->get_components_by_name<CircleCollider>(collisionData.info.other.metadata.name).front().get().active = false;
	this->amount++;
	return true;
}

void CoinScript::init(){
	this->subscribe<CollisionEvent>([this](const CollisionEvent & ev) -> bool { return this->on_collision(ev); });
	this->subscribe<EndGameEvent>([this](const EndGameEvent e)-> bool { return this->save(); });
}

void CoinScript::fixed_update(crepe::duration_t dt) {
	this->trigger_event(GetCoinEvent{
		.amount_of_coins = this->amount,
	});
}

bool CoinScript::save(){
	SaveManager & savemgr = this->get_save_manager();
	savemgr.set(TOTAL_COINS_RUN, this->amount);
	this->amount = 0;
	return false;
}
