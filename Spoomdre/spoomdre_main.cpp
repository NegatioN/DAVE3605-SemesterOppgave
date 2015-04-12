#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "game.hpp"

	

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

	

	Game game;
	game.initialize();


	game.fillRect(rect);
	game.update();
	game.wait(2);

	game.terminate();
	

	return 0;


}