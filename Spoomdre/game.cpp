#include "game.hpp"
#include "player.hpp"
#include "sector.hpp"
#include "vertex.hpp"

Player player;
sector test_sector{1, 10.f, 40.f};
SDL_Rect rect;

//get window surface
void Game::makeRenderer(){
	//renderer = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Game::initialize(int height, int width) {
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
			makeRenderer();
		}
	}

	vertex v1 = vertex{400, 100};
	vertex v2 = vertex{400, 400};
	test_sector.addVertex(v1);
	test_sector.addVertex(v2);

	player.init();
}

void Game::update(std::vector<bool> wasd){
	player.move(wasd);
	//SDL_UpdateWindowSurface(window);
	//fillRect(rect, 0, 0, 0);
}

void Game::render() {
	// empty renderer from previous iteration
    SDL_RenderClear(renderer);

    //fillRect(rect, 0, 0, 0);
    player.render(renderer);
    test_sector.render(renderer);
    // render screen
	SDL_SetRenderDrawColor(renderer, 0,0,0,0); // background-color
    SDL_RenderPresent(renderer); // draw
}

void Game::fillRect(SDL_Rect rect, int r, int g, int b){
	//SDL_FillRect(screenSurface, &rect, SDL_MapRGB(screenSurface->format, r, g, b));
// render commands here
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color
	SDL_RenderDrawRect(renderer, &rect);
}

void Game::terminate(){
	//Destroy renderer
	SDL_DestroyRenderer(renderer);

	//Destroy window
	SDL_DestroyWindow(window);

	//quit SDL Subsystems
	SDL_Quit();
}
void Game::wait(int milliseconds){
	SDL_Delay(milliseconds);
}

void fpsCounter(){
	
}
