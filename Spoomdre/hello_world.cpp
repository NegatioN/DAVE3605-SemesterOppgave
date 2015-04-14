#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>

#include "keyboard_handler.hpp"

//screen dimension constants
const int SCREEN_WIDHT = 640;
const int SCREEN_HEIGHT = 480;

KeyboardHandler keyboard;

float FNcross(float x1, float y1, float x2, float y2) {
	return x1 * y2 - y1 * x2;
}

float intersectX(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y) {
	x = FNcross(x1, y1, x2, y2);
	y = FNcross(x3, y3, x4, y4);
	float det = FNcross(x1-x2, y1-y2, x3-x4, y3-y4);
	x = FNcross(x, x1-x2, y, x3-x4) / det;
	return x;
	//y = FNcross(x, y1-y2, y, y3-y4) / det;
}

float intersectY(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float x, float y) {
	x = FNcross(x1, y1, x2, y2);
	y = FNcross(x3, y3, x4, y4);
	float det = FNcross(x1-x2, y1-y2, x3-x4, y3-y4);
	x = FNcross(x, x1-x2, y, x3-x4) / det;
	y = FNcross(x, y1-y2, y, y3-y4) / det;
	return y;
}

int main( int argc, char* args[]){

	//Window to render to
	SDL_Window* window = NULL;

	// renderer
	SDL_Renderer *renderer = NULL;

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

			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

			//get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill surface with white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(
				screenSurface->format, 0x00, 0x00, 0x00));

			//update surface
			SDL_UpdateWindowSurface(window);

			//wait 2 sec
			//SDL_Delay(2000);
		}
	}

/*
	// coordinates for the middle of the player
	int xp = SCREEN_WIDHT / 2;
	int yp = SCREEN_HEIGHT / 2;
	// player
	SDL_Rect player;
	player.x = xp;
	player.y = yp;
	player.w = 4;
	player.h = 4;

*/
	// example rectangle
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 5;
	rect.h = 5;
	// coordinates for the middle of the rectangle
	//int x = (rect.x + rect.w) - rect.w / 2;
	//int y = (rect.y + rect.h) - rect.h / 2;




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

	// player coordinates
	float px = 150;
	float py = 150;
	float angle = 0;

	// wall coordinates
	float vx1 = 200;
	float vy1 = 100;
	float vx2 = 200;
	float vy2 = 200;

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
        		case SDL_KEYUP:
        			keyboard.handleKeyboardEvent(event.key);
				break;

                // User-requested exit
                case SDL_QUIT:
                	running = false;
                break;
      		}
    	}

		// Exit program if esc-key is pressed
		if (keyboard.isPressed(SDLK_ESCAPE))
            running = false;


		// LOGIC
		
        // keyboard-events
        if (keyboard.isPressed(SDLK_w)) { px = px + cos(angle); py = py + sin(angle); }
        if (keyboard.isPressed(SDLK_a)) { px = px + sin(angle); py = py - cos(angle); }
        if (keyboard.isPressed(SDLK_s)) { px = px - cos(angle); py = py - sin(angle); }
        if (keyboard.isPressed(SDLK_d)) { px = px - sin(angle); py = py + cos(angle); }
        if (keyboard.isPressed(SDLK_q)) { angle = angle - 0.02; }
        if (keyboard.isPressed(SDLK_e)) { angle = angle + 0.02; }
        

		// RENDER


        // empty renderer from previous iteration
        SDL_RenderClear(renderer);

		// transform vertexes relative to player
		float tx1 = vx1 - px;
		float ty1 = vy1 - py;
		float tx2 = vx2 - px;
		float ty2 = vy2 - py;
		//rotate around player
		float tz1 = tx1 * cos(angle) + ty1 * sin(angle);
		float tz2 = tx2 * cos(angle) + ty2 * sin(angle);
		tx1 = tx1 * sin(angle) - ty1 * cos(angle);
		tx2 = tx2 * sin(angle) - ty2 * cos(angle);

		int scale = 250;

		// draw perspective
		if(tz1 > 0 || tz2 > 0) {
			// if line crosses player's viewplaye, clip it
			float ix1 = 0;
			float iz1 = 0;
			float ix2 = 0;
			float iz2 = 0;
			// cross-product calls
			ix1 = intersectX(tx1,tz1, tx2,tz2, -0.0001,0.0001, -20,5, ix1,iz1); iz1 = intersectY(tx1,tz1, tx2,tz2, -0.0001,0.0001, -20,5, ix1,iz1);
			ix2 = intersectX(tx1,tz1, tx2,tz2, 0.0001,0.0001, 20,5, ix2,iz2); iz2 = intersectY(tx1,tz1, tx2,tz2, 0.0001,0.0001, 20,5, ix2,iz2);
			// what to render after cross-product
			if(tz1 <= 0) { if(iz1 > 0) { tx1 = ix1; tz1 = iz1; } else { tx1 = ix2; tz1 = iz2; } }
			if(tz2 <= 0) { if(iz1 > 0) { tx2 = ix1; tz2 = iz1; } else { tx2 = ix2; tz2 = iz2; } }

			float x1 = -tx1 * 16 / tz1;
			float y1a = -scale / tz1;
			float y1b = scale / tz1;
			float x2 = -tx2 * 16 / tz2;
			float y2a = -scale / tz2;
			float y2b = scale / tz2;


			SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color

			// draw walls
			SDL_RenderDrawLine(renderer, scale + x1, scale + y1a, scale + x2, scale + y2a); // top
			SDL_RenderDrawLine(renderer, scale + x1, scale + y1b, scale + x2, scale + y2b); // bottom
			SDL_RenderDrawLine(renderer, scale + x1, scale + y1a, scale + x1, scale + y1b); // left
			SDL_RenderDrawLine(renderer, scale + x2, scale + y2a, scale + x2, scale + y2b); // right
		}
		SDL_SetRenderDrawColor(renderer, 0,0,0,0); // background-color
        SDL_RenderPresent(renderer); // draw


		std::cout << "time since start: " << frametime  << std::endl;

		// delay loop if it's too soon for next frame
		if (SDL_GetTicks() - frametime < interval)
      		SDL_Delay(interval-(SDL_GetTicks()-frametime));

	} // end of game-loop

	// Destroy renderer
    SDL_DestroyRenderer(renderer);

	// Destroy window
	SDL_DestroyWindow(window);

	//quit SDL Subsystems
	SDL_Quit();
	return 0;

}