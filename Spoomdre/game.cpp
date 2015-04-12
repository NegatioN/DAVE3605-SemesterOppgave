#include "game.hpp"

//get window surface
void Game::makeSurface(){
	screenSurface = SDL_GetWindowSurface(window);
}

void Game::initialize(int height, int width){
		//INIT SDL
	if(SDL_Init( SDL_INIT_VIDEO) < 0){
		printf("SDL Could not initialize! SDL_ERROR: %s\n",
			SDL_GetError());
	}else{
		//Create Window
		window = SDL_CreateWindow("SDL Hello World", 
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
			width, height, SDL_WINDOW_SHOWN);
		if(window == NULL)
		{
			printf("Window could not be created! SDL_ERROR: %s\n", 
				SDL_GetError());
		}else{
			makeSurface();
		}
	}
}

void Game::update(){
	SDL_UpdateWindowSurface(window);
}
void Game::fillRect(SDL_Rect rect){
	SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, 0x00, 0xFF, 0xFF));
}

void Game::terminate(){
	//Destroy window
	SDL_DestroyWindow(window);

	//quit SDL Subsystems
	SDL_Quit();
}
void Game::wait(int seconds){
	SDL_Delay(seconds*1000);
}
