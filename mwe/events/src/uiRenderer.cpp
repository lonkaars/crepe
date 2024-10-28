#include "uiRenderer.h"

// Constructor
UIRenderer::UIRenderer(SDL_Renderer* renderer) : renderer(renderer) {}

// Render function
void UIRenderer::render(UIObject* uiObject) {
    if (Button* button = dynamic_cast<Button*>(uiObject)) {
        renderButton(button);
    } else if (Text* text = dynamic_cast<Text*>(uiObject)) {
        renderText(text);
    } else if (TextInput* textInput = dynamic_cast<TextInput*>(uiObject)) {
        renderTextInput(textInput);
    }
}

// Private helper function to render a Button
void UIRenderer::renderButton(Button* button) {
    SDL_Rect buttonRect = {button->x, button->y, button->width, button->height};
    SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255); // Button color
    SDL_RenderFillRect(renderer, &buttonRect);
}

// Private helper function to render a Text
void UIRenderer::renderText(Text* text) {
    if (text->font != nullptr) {
        SDL_Color sdlColor = {text->color.red, text->color.green, text->color.blue, 255};
        SDL_Surface* textSurface = TTF_RenderText_Blended(text->font, text->text.c_str(), sdlColor);
        if (!textSurface) {
            std::cerr << "Error creating text surface: " << TTF_GetError() << std::endl;
            return;
        }

        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (!textTexture) {
            std::cerr << "Error creating texture from surface: " << SDL_GetError() << std::endl;
            SDL_FreeSurface(textSurface);
            return;
        }

        SDL_Rect textRect = {text->x, text->y, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    }
}

// Private helper function to render a TextInput
void UIRenderer::renderTextInput(TextInput* textInput) {
    SDL_Rect inputRect = {textInput->x, textInput->y, textInput->width, textInput->height};
    SDL_SetRenderDrawColor(renderer, textInput->backgroundColor.red, textInput->backgroundColor.green, textInput->backgroundColor.blue, 255);
    SDL_RenderFillRect(renderer, &inputRect);

    // Render text or placeholder
    if (!textInput->textBuffer.empty()) {
        SDL_Color sdlColor = {textInput->textColor.red, textInput->textColor.green, textInput->textColor.blue, 255};
        SDL_Surface* textSurface = TTF_RenderText_Blended(textInput->font, textInput->textBuffer.c_str(), sdlColor);
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        SDL_Rect textRect = {textInput->x + 5, textInput->y + 5, textSurface->w, textSurface->h};
        SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
        SDL_FreeSurface(textSurface);
        SDL_DestroyTexture(textTexture);
    } else if (!textInput->placeholder.empty()) {
        SDL_Color sdlColor = {128, 128, 128, 255};  // Placeholder color
        SDL_Surface* placeholderSurface = TTF_RenderText_Blended(textInput->font, textInput->placeholder.c_str(), sdlColor);
        SDL_Texture* placeholderTexture = SDL_CreateTextureFromSurface(renderer, placeholderSurface);
        SDL_Rect placeholderRect = {textInput->x + 5, textInput->y + 5, placeholderSurface->w, placeholderSurface->h};
        SDL_RenderCopy(renderer, placeholderTexture, nullptr, &placeholderRect);
        SDL_FreeSurface(placeholderSurface);
        SDL_DestroyTexture(placeholderTexture);
    }
}
