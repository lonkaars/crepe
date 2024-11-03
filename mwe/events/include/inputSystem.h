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
	void registerText(Text* label);
	void registerTextInput(TextInput* input);
    void processInput();

private:
    std::vector<Button*> buttons;
	std::vector<TextInput*> textInputs;
	std::vector<Text*> texts;
    void processMouseClick(int mouseX, int mouseY);
	void processInputField(int mouseX, int mouseY);
	void processKeyPress(Keycode);
	void processTextInput(const std::string& text);
	
};
