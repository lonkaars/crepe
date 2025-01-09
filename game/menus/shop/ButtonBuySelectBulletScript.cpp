#include "ButtonBuySelectBulletScript.h"
#include "../MenusConfig.h"
#include "Config.h"
#include "ValueBroker.h"
#include "manager/SaveManager.h"
#include "menus/shop/Shopconfig.h"

using namespace crepe;
using namespace std;

void ButtonBuySelectBulletScript::init() {
	IButtonScript::init();
	this->subscribe<ButtonPressEvent>([this](const ButtonPressEvent & e) {
		return this->on_button_press(e);
	});
}

bool ButtonBuySelectBulletScript::on_button_press(const ButtonPressEvent & e) {
	SaveManager & save = this->get_save_manager();
	ValueBroker<int> buy_bullet = save.get<int>(BUY_BULLET_SAVE,0);
	if(!buy_bullet.get()){
		ValueBroker<int> coins = save.get<int>(TOTAL_COINS_GAME,0);
		if(coins.get() >= 0)
		{
			int coin = coins.get();
			coin -= 0;
			save.set(TOTAL_COINS_GAME,coin);
			save.set(BUY_BULLET_SAVE,1);
		}
	}
	else {
		save.set(JETPACK_PARTICLES,0);
	}
	this->trigger_event<ShopUpdate>();
	return false;
}
