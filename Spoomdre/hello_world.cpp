#include <SDL2/SDL.h>
#include <stdio.h>

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
			SDL_Delay(2000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//quit SDL Subsystems
	SDL_Quit();
	return 0;

}