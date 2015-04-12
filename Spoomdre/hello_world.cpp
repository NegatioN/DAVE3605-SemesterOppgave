#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

//screen dimension constants
const int SCREEN_WIDHT = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[]){

	//Window to render to
	SDL_Window* window = NULL;

	//surface of window
	SDL_Surface* screenSurface = NULL;

	//INIT SDL
	if(SDL_Init( SDL_INIT_VIDEO) < 0){
		printf("SDL Could not initialize! SDL_ERROR: %s\n",
			SDL_GetError());
	}else{
		//Create Window
		window = SDL_CreateWindow("SDL Hello World", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			SCREEN_WIDHT, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			printf("Window could not be created! SDL_ERROR: %s\n", 
				SDL_GetError());
		}else{

			//get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill surface with white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(
				screenSurface->format, 0xFF, 0xFF, 0xFF));

			//update surface
			SDL_UpdateWindowSurface(window);

			//wait 2 sec
			//SDL_Delay(2000);
		}
	}



	// example rectangle
	SDL_Rect rect;
	rect.x = 200;
	rect.y = 150;
	rect.w = 200;
	rect.h = 200;
	// coordinates for the middle of the rectangle
	int x = (rect.w-rect.x) / 2;
	int y = (rect.h-rect.y) / 2;


	// Holds the next event to be handled, ie keyboard-press
	SDL_Event event;
	// time for current frame
	Uint32 frametime;
	// frames per second
	Uint32 fps = 50;
	// interval between each frame in millisec
	Uint32 interval = 1000 / fps;
	// if game is still running
	bool running = true;
	// game-loop

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
        		// Exit program if esc-key is pressed
        		if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;

                // wasd for movement, should be moved to a seperate KeyboardHandler
                if (event.key.keysym.sym == SDLK_w)
                    rect.y -= 2;
                if (event.key.keysym.sym == SDLK_a)
                    rect.x -= 2;
                if (event.key.keysym.sym == SDLK_s)
                    rect.y += 2;
                if (event.key.keysym.sym == SDLK_d)
                    rect.x += 2;

				break;

                // User-requested exit
                case SDL_QUIT:
                	running = false;
                break;
      		}
    	}



		// LOGIC
		
		// RENDER

    	// clears screen
		SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
		// filling surface with rect
		SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0xFF));
		//update surface
		SDL_UpdateWindowSurface(window);


		std::cout << "time since start: " << frametime  << std::endl;

		// delay loop if it's too soon for next frame
		if (SDL_GetTicks() - frametime < interval)
      		SDL_Delay(interval-(SDL_GetTicks()-frametime));

	} // end of game-loop


	//Destroy window
	SDL_DestroyWindow(window);

	//quit SDL Subsystems
	SDL_Quit();
	return 0;

}