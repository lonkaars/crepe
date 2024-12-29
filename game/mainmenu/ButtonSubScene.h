#pragma once

#include <crepe/api/GameObject.h>
#include "MainMenuConfig.h"

namespace crepe {
class Scene;
}

class ButtonSubScene {
public:
	//script enum
	enum class ScriptSelect {
		PREVIEW,
		SHOP,
		MAINMENU,
		NONE,
	};
	//icon enum
	enum class IconSelect {
		SHOP,
		NONE,
	};
	//icon enum
	enum class ButtonSelect {
		SMALL,
		LARGE,
	};
	//data struct
	struct Data{
		const std::string & text = "NODATA";
		const crepe::vec2 & text_offset = {0,0};
		const float text_width = 200;
		const crepe::vec2 & icon_offset = {0,0};
		const IconSelect icon_type = IconSelect::NONE;
		const crepe::vec2 & position = {0,0};
		const ScriptSelect script_type = ScriptSelect::NONE;
		const ButtonSelect button_type = ButtonSelect::LARGE;
		const float scale = 1;
	};
public:
	void create(crepe::Scene & scn,const Data & data);
private:
	void large_btn_overlay(crepe::GameObject & button_object);
	void small_btn_overlay(crepe::GameObject & button_object);
	void btn_color_side(crepe::GameObject & button_object,const crepe::vec2 & offset);
	void btn_text(crepe::GameObject & button_object,const Data & data);
	void set_script(crepe::GameObject & button_object,const Data & data);
	void set_icon(crepe::GameObject & button_object,const Data & data);
	void set_button_overlay(crepe::GameObject & button_object,const Data & data);
private:
	static constexpr crepe::vec2 SIDE_PANEL_OFFSET = {113,0};
};
