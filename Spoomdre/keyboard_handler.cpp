#include "keyboard_handler.hpp"

void KeyboardHandler::handleKeyboardEvent(SDL_KeyboardEvent key) {
	// sets keystate
	keyStates[key.keysym.sym] = (key.type == SDL_KEYDOWN) ? true : false;
}

bool KeyboardHandler::isPressed(int keyCode) {
	return keyStates[keyCode];
}

bool KeyboardHandler::isReleased(int keyCode) {
	return !keyStates[keyCode];
}
