#include "inputSystem.h"

InputSystem::InputSystem() {}

void InputSystem::registerButton(Button* button) {
    buttons.push_back(button);
}

void InputSystem::processInput() {
	
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                triggerEvent(ShutDownEvent());
                break;
            case SDL_KEYDOWN:
                triggerEvent(KeyPressedEvent(getCustomKey(event.key.keysym.sym)));
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
    for (auto* button : buttons) {
        if (mouseX >= button->x && mouseX <= (button->x + button->width) &&
            mouseY >= button->y && mouseY <= (button->y + button->height)) {
            button->onClick();
        }
    }
}

