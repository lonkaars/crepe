#include "uiRenderer.h"

// Constructor
UIRenderer::UIRenderer(SDL_Renderer * renderer) : renderer(renderer) {}

// Render function
void UIRenderer::render(UIObject * uiObject) {
	if (Button * button = dynamic_cast<Button *>(uiObject)) {
		renderButton(button);
	} else if (Text * text = dynamic_cast<Text *>(uiObject)) {
		renderText(text);
	} else if (TextInput * textInput = dynamic_cast<TextInput *>(uiObject)) {
		renderTextInput(textInput);
	}
}

// Private helper function to render a Button
void UIRenderer::renderButton(Button * button) {
	SDL_Rect buttonRect = {button->x, button->y, button->width, button->height};
	SDL_SetRenderDrawColor(renderer, 100, 100, 255, 255); // Button color
	SDL_RenderFillRect(renderer, &buttonRect);
}

// Private helper function to render a Text
void UIRenderer::renderText(Text * text) {
	if (text->font != nullptr) {
		SDL_Color sdlColor = {text->color.red, text->color.green, text->color.blue, 255};
		SDL_Surface * textSurface
			= TTF_RenderText_Blended(text->font, text->text.c_str(), sdlColor);
		if (!textSurface) {
			std::cerr << "Error creating text surface: " << TTF_GetError() << std::endl;
			return;
		}

		SDL_Texture * textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
		if (!textTexture) {
			std::cerr << "Error creating texture from surface: " << SDL_GetError()
					  << std::endl;
			SDL_FreeSurface(textSurface);
			return;
		}

		SDL_Rect textRect = {text->x, text->y, textSurface->w, textSurface->h};
		SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
		SDL_FreeSurface(textSurface);
		SDL_DestroyTexture(textTexture);
	}
}

void UIRenderer::renderTextInput(TextInput * textInput) {
	// // Check if textInput or renderer is null to avoid segmentation faults
	// if (!textInput || !renderer) {
	//     std::cerr << "Error: Null pointer detected for textInput or renderer." << std::endl;
	//     return;
	// }

	// // Render the background rectangle for the text input
	// SDL_Rect inputRect = {textInput->x, textInput->y, textInput->width, textInput->height};
	// SDL_SetRenderDrawColor(renderer, textInput->backgroundColor.red, textInput->backgroundColor.green, textInput->backgroundColor.blue, 255);
	// SDL_RenderFillRect(renderer, &inputRect);

	// // Check if font is valid
	// if (!textInput->font) {
	//     std::cerr << "Error: Font is not loaded for textInput." << std::endl;
	//     return;
	// }

	// SDL_Color sdlColor = {textInput->textColor.red, textInput->textColor.green, textInput->textColor.blue, 255};

	// if (!textInput->textBuffer.empty()) {
	//     // Render the text in the input field
	//     SDL_Surface* textSurface = TTF_RenderText_Blended(textInput->font, textInput->textBuffer.c_str(), sdlColor);
	//     if (textSurface) {
	//         SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//         if (textTexture) {
	//             SDL_Rect textRect = {textInput->x + 5, textInput->y + 5, textSurface->w, textSurface->h};
	//             SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
	//             SDL_DestroyTexture(textTexture);
	//         } else {
	//             std::cerr << "Error: Unable to create texture from text surface." << std::endl;
	//         }
	//         SDL_FreeSurface(textSurface);
	//     } else {
	//         std::cerr << "Error: Unable to create text surface." << std::endl;
	//     }
	// } else if (!textInput->placeholder.empty()) {
	//     // Render the placeholder text
	//     SDL_Color placeholderColor = {128, 128, 128, 255}; // Light gray for placeholder
	//     SDL_Surface* placeholderSurface = TTF_RenderText_Blended(textInput->font, textInput->placeholder.c_str(), placeholderColor);
	//     if (placeholderSurface) {
	//         SDL_Texture* placeholderTexture = SDL_CreateTextureFromSurface(renderer, placeholderSurface);
	//         if (placeholderTexture) {
	//             SDL_Rect placeholderRect = {textInput->x + 5, textInput->y + 5, placeholderSurface->w, placeholderSurface->h};
	//             SDL_RenderCopy(renderer, placeholderTexture, nullptr, &placeholderRect);
	//             SDL_DestroyTexture(placeholderTexture);
	//         } else {
	//             std::cerr << "Error: Unable to create texture from placeholder surface." << std::endl;
	//         }
	//         SDL_FreeSurface(placeholderSurface);
	//     } else {
	//         std::cerr << "Error: Unable to create placeholder surface." << std::endl;
	//     }
	// }
}
