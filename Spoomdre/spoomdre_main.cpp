#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "game.hpp"

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]){
//DECLARE TEST VARIABLES

	SDL_Rect rect;
	rect.x = 200;
	rect.y = 150;
	rect.w = 200;
	rect.h = 200;
	// coordinates for the middle of the rectangle
	int x = (rect.w-rect.x) / 2;
	int y = (rect.h-rect.y) / 2;

	//SDL-VARIABLES
	Game game;			//SDL_WINDOW + SDL_SURFACE
	SDL_Event event;	// Holds the next event to be handled (user-input)

	game.initialize(SCREEN_HEIGHT, SCREEN_WIDTH);
	//SDL_Window 
	int R = 0x00;
	bool running = true;

	while(running){
		std::cout << "Rendering, R=" << R << std::endl;
		R+=10;
		game.fillRect(rect, R, R, R);
		game.update();
		game.wait(1);
		if(R > 150)
			running = false;
	}

	game.terminate();
	

	return 0;


}