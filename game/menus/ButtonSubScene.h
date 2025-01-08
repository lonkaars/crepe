#pragma once

#include <crepe/api/GameObject.h>

#include <string>

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
		NEXT,
		REPLAY,
		CREDITS_SHOW,
		CREDITS_BACK,
		NONE,
	};
	//icon enum
	enum class IconSelect {
		SHOP,
		COINS,
		NONE,
	};
	//icon enum
	enum class ButtonSelect {
		BACK,
		NEXT,
		LARGE,
	};
	//data struct
	struct Data {
		const std::string & text = "NODATA";
		const crepe::vec2 & text_offset = {0, 0};
		const float text_width = 200;
		const crepe::vec2 & icon_offset = {0, 0};
		const IconSelect icon_type = IconSelect::NONE;
		const crepe::vec2 & position = {0, 0};
		const ScriptSelect script_type = ScriptSelect::NONE;
		const ButtonSelect button_type = ButtonSelect::LARGE;
		const float scale = 1;
		const bool worldspace = true;
		const bool color_side = true;
		const std::string & tag = "";
		const int sorting_layer_offset = 0;
	};

public:
	void create(crepe::Scene & scn, const Data & data);

private:
	void large_btn_overlay(crepe::GameObject & button_object, const Data & data);
	void back_btn_overlay(crepe::GameObject & button_object, const Data & data);
	void next_btn_overlay(crepe::GameObject & button_object, const Data & data);
	void btn_color_side(
		crepe::GameObject & button_object, const crepe::vec2 & offset, const Data & data
	);
	void btn_text(crepe::GameObject & button_object, const Data & data);
	void set_script(crepe::GameObject & button_object, const Data & data);
	void set_icon(crepe::GameObject & button_object, const Data & data);
	void set_button_overlay(crepe::GameObject & button_object, const Data & data);

private:
	static constexpr crepe::vec2 SIDE_PANEL_OFFSET = {113, 0};
};
