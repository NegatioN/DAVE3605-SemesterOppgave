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
	//surface = SDL_GetWindowSurface(window);
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

	width_ = width;
	height_ = height;

	createWorld();
	Vector3f position(width/2, height/2, 20);
	//player{position};
	//player.init(width/2, height/2, 20); // x, y, z
	player.init(position); // x, y, z
}

void Game::update(std::vector<bool> wasd, int mouse_x, int mouse_y){
	player.setMoveVector(wasd);
	player.setMouseValues(mouse_x, mouse_y);
	player.move();
}

void Game::render() {
	// empty renderer from previous iteration
    SDL_RenderClear(renderer);

    // render player & world
    //player.render(renderer);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color
    test_sector.render(renderer, player.x(), player.y(), player.z(), player.angle(), player.yaw());

    // render crosshair
    SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xAA);
    SDL_RenderDrawLine(renderer, width_/2-10, height_/2, width_/2+10, height_/2);
    SDL_RenderDrawLine(renderer, width_/2, height_/2-10, width_/2, height_/2+10);

    // render screen
	SDL_SetRenderDrawColor(renderer, 0,0,0,0); // background-color
    SDL_RenderPresent(renderer); // draw
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

void Game::createWorld(){

		/* // old hexagon
	vertex v1 = vertex{200, 100};
	vertex v2 = vertex{400, 100};
	vertex v3 = vertex{500, 300};
	vertex v4 = vertex{400, 500};
	vertex v5 = vertex{200, 500};
	vertex v6 = vertex{100, 300};

	test_sector.addVertex(v1);
	test_sector.addVertex(v2);
	test_sector.addVertex(v3);
	test_sector.addVertex(v4);
	test_sector.addVertex(v5);
	test_sector.addVertex(v6);*/

	// vertexes for test-map
	vertex v1 = vertex{200, 200};
	vertex v2 = vertex{400, 100};
	vertex v3 = vertex{500, 200};
	vertex v4 = vertex{500, 300};
	vertex v5 = vertex{400, 400};
	vertex v6 = vertex{500, 500};
	vertex v7 = vertex{600, 300};
	vertex v8 = vertex{700, 500};
	vertex v9 = vertex{600, 700};
	vertex v10= vertex{400, 700};
	vertex v11= vertex{200, 600};
	vertex v12= vertex{100, 400};

	test_sector.addVertex(v1);
	test_sector.addVertex(v2);
	test_sector.addVertex(v3);
	test_sector.addVertex(v4);
	test_sector.addVertex(v5);
	test_sector.addVertex(v6);
	test_sector.addVertex(v7);
	test_sector.addVertex(v8);
	test_sector.addVertex(v9);
	test_sector.addVertex(v10);
	test_sector.addVertex(v11);
	test_sector.addVertex(v12);
}
