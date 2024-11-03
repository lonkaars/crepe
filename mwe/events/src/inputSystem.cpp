#include "inputSystem.h"

InputSystem::InputSystem() {}

void InputSystem::registerButton(Button * button) { buttons.push_back(button); }
void InputSystem::registerTextInput(TextInput * input) {
	textInputs.push_back(input);
}
void InputSystem::registerText(Text * label) { texts.push_back(label); }

void InputSystem::processInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				triggerEvent(ShutDownEvent());
				break;
			case SDL_KEYDOWN:
				triggerEvent(
					KeyPressedEvent(getCustomKey(event.key.keysym.sym)));
				processKeyPress(event.key.keysym.sym);
				break;
			case SDL_TEXTINPUT:
				// Process typed characters
				processTextInput(event.text.text);
				break;
			case SDL_MOUSEBUTTONDOWN: {
				int mouseX, mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				processMouseClick(mouseX, mouseY);
				triggerEvent(MousePressedEvent(mouseX, mouseY));
				break;
			}
		}
	}
}

void InputSystem::processMouseClick(int mouseX, int mouseY) {
	for (auto * button : buttons) {
		if (mouseX >= button->x && mouseX <= (button->x + button->width)
			&& mouseY >= button->y && mouseY <= (button->y + button->height)) {
			button->onClick();
		}
	}
	for (auto * textInput : textInputs) {
		if (mouseX >= textInput->x && mouseX <= textInput->x + textInput->width
			&& mouseY >= textInput->y
			&& mouseY <= textInput->y + textInput->height) {
			textInput->isActive = true;
		} else {
			textInput->isActive = false;
		}
	}
}
void InputSystem::processKeyPress(Keycode key) {
	// for (auto* textInput : textInputs) {
	//     if (textInput->isActive) {
	//         if (key == SDLK_RETURN || key == SDLK_KP_ENTER) {
	//             // Submit the text
	//             if (textInput->onSubmit) {
	//                 textInput->onSubmit();
	//             }
	//         }
	//         else if (key == SDLK_BACKSPACE) {
	//             // Handle backspace
	//             if (!textInput->textBuffer.empty() && textInput->caretPosition > 0) {
	//                 textInput->textBuffer.erase(textInput->caretPosition - 1, 1);
	//                 textInput->caretPosition--;
	//             }
	//         }
	//         else if (key == SDLK_LEFT) {
	//             // Move caret left
	//             if (textInput->caretPosition > 0) {
	//                 textInput->caretPosition--;
	//             }
	//         }
	//         else if (key == SDLK_RIGHT) {
	//             // Move caret right
	//             if (textInput->caretPosition < textInput->textBuffer.size()) {
	//                 textInput->caretPosition++;
	//             }
	//         }
	//     }
	// }
}

void InputSystem::processTextInput(const std::string & text) {
	// for (auto* textInput : textInputs) {
	//     if (textInput->isActive) {
	//         // Insert text at caret position
	//         textInput->textBuffer.insert(textInput->caretPosition, text);
	//         textInput->caretPosition += text.length();
	//     }
	// }
}
