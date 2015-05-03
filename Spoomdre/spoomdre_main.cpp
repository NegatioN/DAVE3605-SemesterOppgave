#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include "game.hpp"
//#include "keyboard_handler.hpp"
#include <Eigen/Dense>

#include <vector>

//screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//KeyboardHandler keyboardHandler;

int main(int argc, char* args[]){
    //HINTS for SDL - Do not remove without proper testing
    SDL_SetHintWithPriority(SDL_HINT_MOUSE_RELATIVE_MODE_WARP, "1", SDL_HINT_OVERRIDE); 

	//Functionality-providing variables
	
	Game game;			//SDL_WINDOW + SDL_SURFACE
	SDL_Event event;	// Holds the next event to be handled (user-input)

	std::vector<bool> keys;
	for(int i = 0; i < 14; i++) // values for keyboard-keys (movement) & km (rotation)
		keys.push_back(false);

	//init variables
	game.initialize(SCREEN_HEIGHT, SCREEN_WIDTH);
	bool running = true;


	// time for current frame
	Uint32 lastTime = SDL_GetTicks(); // time of last iteration
    Uint32 timer = SDL_GetTicks();    // timer for updating info each sec
    double delta = 0;                 // waiting-time before next update
    int frames = 0;                   // counter for fps
    int updates = 0;                  // counter for tps (ticks-per-sec)
	Uint32 fps = 50;                  // wanted fps
	double interval = 1000 / fps;     // time between each tick in msec

    //Limit mouse to being inside window-bounds
    //this unfortunately doesn't work perfectly on linux VM, it seems
    SDL_SetRelativeMouseMode(SDL_TRUE);

	//START GAME-LOOP
	while(running) {

        // Calculate time-stuff
        Uint32 now = SDL_GetTicks();
        delta += (double)(now - lastTime) / interval;
        lastTime = now;

        while(delta >= 1) {

            // EVENTS
            // Polls/gets any pending events
            while (SDL_PollEvent (&event) != 0) {
                // what type of event
                bool state = false;
                int code = -1;
                switch (event.type)
                {
                    // Keyboard-Event
                    case SDL_KEYDOWN:
                        state = true;
                    case SDL_KEYUP:
                        code = event.key.keysym.sym;
                        if      (code == SDLK_w)        keys.at(0) = state;     // up
                        else if (code == SDLK_a)        keys.at(1) = state;     // left
                        else if (code == SDLK_s)        keys.at(2) = state;     // down
                        else if (code == SDLK_d)        keys.at(3) = state;     // right
                        else if (code == SDLK_RIGHT)    keys.at(4) = state;     // turn right
                        else if (code == SDLK_l)        keys.at(4) = state;     // -----||-----
                        else if (code == SDLK_LEFT)     keys.at(5) = state;     // turn left
                        else if (code == SDLK_k)        keys.at(5) = state;     // -----||-----
                        else if (code == SDLK_UP)       keys.at(6) = state;     // look up
                        else if (code == SDLK_DOWN)     keys.at(7) = state;     // look down
                        else if (code == SDLK_LCTRL)    keys.at(8) = state;     // crouch
                        else if (code == SDLK_c)        keys.at(8) = state;     // -----||-----
                        else if (code == SDLK_SPACE)    keys.at(9) = state;     // jump
                        else if (code == SDLK_RETURN)   keys.at(10) = state;    // shoot
                        else if (code == SDLK_e)        keys.at(11) = state;    // evnt/interact
                        else if (code == SDLK_LSHIFT)   keys.at(12) = state;    // sprint
                        else if (code == SDLK_BACKSPACE)keys.at(13) = state;    // respawn

                        // Pressed ESC-key, close program
                        else if (code == SDLK_ESCAPE && state) running = false;
                    break;
                    // Mouse-Events
                    case SDL_MOUSEBUTTONDOWN:
                        state = true;
                    case SDL_MOUSEBUTTONUP:
                        code = event.button.button;
                        if      (code == SDL_BUTTON_LEFT) keys.at(10) = state;  // shoot
                    break;
                        
                    // User-requested exit
                    case SDL_QUIT:
                        running = false;
                    break;
                } // end of switch-case
            } // end of event-loop

            // get any mouse-changes since last frame
            int mx; int my;
            SDL_GetRelativeMouseState(&mx, &my);

            // update game logic
            game.update(keys, mx, my);

            // update time-stuff
            updates++;
            delta--;
        } // end of delta-loop

        // render outside of update-loop to use fps as benchmark
		game.render();
        frames++;

        // prints frames-per-second & ticks-per-second, every second
        if(SDL_GetTicks() - timer >= 1000) {
            std::cout << "tps: " << updates << ", fps: " << frames << std::endl;
            timer += 1000;
            frames = 0;
            updates = 0;
        }

	} // end of game-loop

    //finalize SDL-variables
	game.terminate();

	return 0;
}