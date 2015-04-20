#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "game.hpp"
#include "keyboard_handler.hpp"
#include <Eigen/Dense>

#include <vector>

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

KeyboardHandler keyboardHandler;

int main(int argc, char* args[]){
	//Functionality-providing variables
	
	Game game;			//SDL_WINDOW + SDL_SURFACE
	SDL_Event event;	// Holds the next event to be handled (user-input)

	std::vector<bool> wasd;
	for(int i = 0; i < 8; i++) // values for wasd (movement) & km (rotation)
		wasd.push_back(false);

	//init variables
	game.initialize(SCREEN_HEIGHT, SCREEN_WIDTH);
	bool running = true;

	// time for current frame
	Uint32 frametime;
	// frames per second
	Uint32 fps = 50;
	// interval between each frame in millisec
	Uint32 interval = 1000 / fps;

	//START GAME-LOOP
	while(running) {

		// update time for current frame
		frametime = SDL_GetTicks();

		// EVENTS
		// Polls/gets any pending events
		while (SDL_PollEvent (&event) != 0) {
			// what type of event
      		switch (event.type)
      		{
      			// Keyboard-press
        		case SDL_KEYDOWN:
        			if(event.key.keysym.sym == SDLK_w) wasd.at(0) = true;
        			if(event.key.keysym.sym == SDLK_a) wasd.at(1) = true;
        			if(event.key.keysym.sym == SDLK_s) wasd.at(2) = true;
        			if(event.key.keysym.sym == SDLK_d) wasd.at(3) = true;
        			if(event.key.keysym.sym == SDLK_RIGHT) wasd.at(4) = true;
        			if(event.key.keysym.sym == SDLK_LEFT) wasd.at(5) = true;
        			if(event.key.keysym.sym == SDLK_UP) wasd.at(6) = true;
        			if(event.key.keysym.sym == SDLK_DOWN) wasd.at(7) = true;
        			keyboardHandler.handleKeyboardEvent(event.key);
        		break;
        		case SDL_KEYUP:
        			if(event.key.keysym.sym == SDLK_w) wasd.at(0) = false;
        			if(event.key.keysym.sym == SDLK_a) wasd.at(1) = false;
        			if(event.key.keysym.sym == SDLK_s) wasd.at(2) = false;
        			if(event.key.keysym.sym == SDLK_d) wasd.at(3) = false;
        			if(event.key.keysym.sym == SDLK_RIGHT) wasd.at(4) = false;
        			if(event.key.keysym.sym == SDLK_LEFT) wasd.at(5) = false;
        			if(event.key.keysym.sym == SDLK_UP) wasd.at(6) = false;
        			if(event.key.keysym.sym == SDLK_DOWN) wasd.at(7) = false;
        			keyboardHandler.handleKeyboardEvent(event.key);
        		break;
        			
                // User-requested exit
                case SDL_QUIT:
                	running = false;
                break;
      		}
    	}

		// Exit program if esc-key is pressed
		if (keyboardHandler.isPressed(SDLK_ESCAPE))
        	running = false;

        // get any mouse-changes since last frame
        int mx; int my;
        SDL_GetRelativeMouseState(&mx, &my);

		game.update(wasd, mx, my);
		game.render();

		// game-loop timer check
		if (SDL_GetTicks() - frametime < interval)
      		game.wait(interval-(SDL_GetTicks()-frametime));
	}

	game.terminate();

	return 0;
}