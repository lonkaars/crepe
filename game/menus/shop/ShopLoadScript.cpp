#include "ShopLoadScript.h"
#include <crepe/ValueBroker.h>
#include "api/Button.h"
#include "api/Sprite.h"
#include "Shopconfig.h"
#include "api/Text.h"
#include "manager/SaveManager.h"

using namespace crepe;
using namespace std;

void ShopLoadScript::init() {
	this->update();
	this->subscribe<ShopUpdate>([this](const ShopUpdate e) {
		return this->update();
	});
}

bool ShopLoadScript::update(){
	SaveManager & save = this->get_save_manager();
	ValueBroker<int> buy_bullet = save.get<int>(BUY_BULLET_SAVE,0);
	ValueBroker<int> buy_bubble = save.get<int>(BUY_BUBBLE_SAVE,0);


	if(buy_bullet.get()){
		auto sprites = this->get_components_by_tag<Sprite>(BUY_BULLET);
		for(auto sprite : sprites){
			sprite.get().active = false;
		}
		auto buttons = this->get_components_by_tag<Button>(BUY_BULLET);
		for(auto btn : buttons){
			btn.get().active = false;
		}
		auto texts = this->get_components_by_tag<Text>(BUY_BULLET);
		for(auto txt : texts){
			txt.get().active = false;
		}
		auto sprites1 = this->get_components_by_tag<Sprite>(SELECT_BULLET);
		for(auto sprite : sprites1){
			sprite.get().active = true;
		}
		auto buttons1 = this->get_components_by_tag<Button>(SELECT_BULLET);
		for(auto btn : buttons1){
			btn.get().active = true;
		}
		auto texts1 = this->get_components_by_tag<Text>(SELECT_BULLET);
		for(auto txt : texts1){
			txt.get().active = true;
		}
	}
	else {
		auto sprites = this->get_components_by_tag<Sprite>(SELECT_BULLET);
		for(auto sprite : sprites){
			sprite.get().active = false;
		}
		auto buttons = this->get_components_by_tag<Button>(SELECT_BULLET);
		for(auto btn : buttons){
			btn.get().active = false;
		}
		auto texts = this->get_components_by_tag<Text>(SELECT_BULLET);
		for(auto txt : texts){
			txt.get().active = false;
		}
		auto sprites1 = this->get_components_by_tag<Sprite>(BUY_BULLET);
		for(auto sprite : sprites1){
			sprite.get().active = true;
		}
		auto buttons1 = this->get_components_by_tag<Button>(BUY_BULLET);
		for(auto btn : buttons1){
			btn.get().active = true;
		}
		auto texts1 = this->get_components_by_tag<Text>(BUY_BULLET);
		for(auto txt : texts1){
			txt.get().active = true;
		}
	}

	if(buy_bubble.get()){
		auto sprites = this->get_components_by_tag<Sprite>(BUY_BUBBLE);
		for(auto sprite : sprites){
			sprite.get().active = false;
		}
		auto buttons = this->get_components_by_tag<Button>(BUY_BUBBLE);
		for(auto btn : buttons){
			btn.get().active = false;
		}
		auto texts = this->get_components_by_tag<Text>(BUY_BUBBLE);
		for(auto txt : texts){
			txt.get().active = false;
		}
		auto sprites1 = this->get_components_by_tag<Sprite>(SELECT_BUBBLE);
		for(auto sprite : sprites1){
			sprite.get().active = true;
		}
		auto buttons1 = this->get_components_by_tag<Button>(SELECT_BUBBLE);
		for(auto btn : buttons1){
			btn.get().active = true;
		}
		auto texts1 = this->get_components_by_tag<Text>(SELECT_BUBBLE);
		for(auto txt : texts1){
			txt.get().active = true;
		}
	}
	else {
		auto sprites = this->get_components_by_tag<Sprite>(SELECT_BUBBLE);
		for(auto sprite : sprites){
			sprite.get().active = false;
		}
		auto buttons = this->get_components_by_tag<Button>(SELECT_BUBBLE);
		for(auto btn : buttons){
			btn.get().active = false;
		}
		auto texts = this->get_components_by_tag<Text>(SELECT_BUBBLE);
		for(auto txt : texts){
			txt.get().active = false;
		}
		auto sprites1 = this->get_components_by_tag<Sprite>(BUY_BUBBLE);
		for(auto sprite : sprites1){
			sprite.get().active = true;
		}
		auto buttons1 = this->get_components_by_tag<Button>(BUY_BUBBLE);
		for(auto btn : buttons1){
			btn.get().active = true;
		}
		auto texts1 = this->get_components_by_tag<Text>(BUY_BUBBLE);
		for(auto txt : texts1){
			txt.get().active = true;
		}
	}
	return false;
}
