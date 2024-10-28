#pragma once
#include <vector>
#include "uiObject.h"
#include "event.h"
#include "keyCodes.h"
#include "eventManager.h"
class InputSystem {
public:
    InputSystem();
    void registerButton(Button* button);
    void processInput();

private:
    std::vector<Button*> buttons;
    void processMouseClick(int mouseX, int mouseY);
};
