#include "keyboard_handler.hpp"

void KeyboardHandler::handleKeyboardEvent(SDL_KeyboardEvent key) {
	// sets keystate
	if(key.keysym.sym > 127) return;
	keyStates[key.keysym.sym] = (key.type == SDL_KEYDOWN) ? true : false;
}

bool KeyboardHandler::isPressed(int keyCode) {
	if(keyCode > 127) return false;
	return keyStates[keyCode];
}

bool KeyboardHandler::isReleased(int keyCode) {
	if(keyCode > 127) return true;
	return !keyStates[keyCode];
}

void KeyboardHandler::clear() {
	/*for(int i = 0; i < keyStates.length; i++) {
		keyStates[i] = false;
	}*/
}
