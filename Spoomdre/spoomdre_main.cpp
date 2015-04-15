#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "game.hpp"
#include "keyboard_handler.hpp"
#include <Eigen/Dense>

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char* args[]){
//Functionality-providing variables
	KeyboardHandler keyboardHandler;
	Game game;			//SDL_WINDOW + SDL_SURFACE
	SDL_Event event;	// Holds the next event to be handled (user-input)

//init variables
	game.initialize(SCREEN_HEIGHT, SCREEN_WIDTH);
	bool running = true;

//DECLARE TEST VARIABLES

	SDL_Rect rect;
	rect.x = 200;
	rect.y = 150;
	rect.w = 200;
	rect.h = 200;
	// coordinates for the middle of the rectangle
	int x = (rect.x + rect.w) - rect.w / 2;
	int y = (rect.y + rect.h) - rect.h / 2;



	int R = 0x00;


	//START GAME-LOOP
	while(running){


		// EVENTS
		// Polls/gets any pending events
		while (SDL_PollEvent (&event) != 0) {
			// what type of event
      		switch (event.type)
      		{
      			// Keyboard-press
        		case SDL_KEYDOWN:
        			keyboardHandler.handleKeyboardEvent(event.key);
        		break;
        		case SDL_KEYUP:
        			//keyboardHandler.handleKeyboardEvent(event.key);
				break;

                // User-requested exit
                case SDL_QUIT:
                	running = false;
                break;
      		}
    	}

		// Exit program if esc-key is pressed
		//if (keyboardHandler.isPressed(SDLK_ESCAPE))
        //    running = false;

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