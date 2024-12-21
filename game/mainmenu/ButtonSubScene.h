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
		START,
		PREVIEW,
		SHOP,
		NONE,
	};
	//data struct
	struct Data{
		const std::string & text = "NODATA";
		const crepe::vec2 & text_offset = {0,0};
		const crepe::vec2 & text_size = {200,200};
		const crepe::vec2 & position = {0,0};
		const ScriptSelect script = ScriptSelect::NONE;
	};
public:
	void create(crepe::Scene & scn,const Data & data);
private:
	void large_btn_overlay(crepe::GameObject & button_object);
	void btn_color_side(crepe::GameObject & button_object,const crepe::vec2 & offset);
	void btn_text_middle(crepe::GameObject & button_object,const std::string & text,const crepe::vec2 & text_offset,const crepe::vec2 & text_size);
	void set_script(crepe::GameObject & button_object,ScriptSelect script);
private:
	static constexpr crepe::vec2 SIDE_PANEL_OFFSET = {113,0};
};
