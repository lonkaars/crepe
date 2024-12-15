#pragma once

#include <crepe/api/Script.h>

class MainMenuScript : public crepe::Script {
public:
    enum class MenuTab {
				NONE,
        JETPACK,
        PREVIEW,
    };
    void switch_tab(MenuTab tab);
private:
    MenuTab current_tab;

    void init() override;
    void update() override;
};
