#ifndef CLASS_KEYBOARDHANDLER_H
#define CLASS_KEYBOARDHANDLER_H


#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>


//Defines keyboard-handling processes
class KeyboardHandler{

	// each keyboard-key has its own value, being the index in the array
	bool keyStates[128];
public:
	void handleKeyboardEvent(SDL_KeyboardEvent event);
	bool isPressed(int keyCode);
	bool isReleased(int keyCode);
};


#endif