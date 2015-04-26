#include "game.hpp"
#include "player.hpp"
#include "sector.hpp"
#include "vertex.hpp"
#include "mapmaker.hpp"
#include "render_util.hpp"

#include <sstream>
#include <fstream>

Player player;
std::vector<sector*> sectors;
SDL_Rect rect;

int MAP = 0;

//get window surface
void Game::makeRenderer(){
	//renderer = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	/*texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, 640, 480);*/
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

	if(MAP == 0)
		sectors = mapmaker::createMap();
	else if(MAP == 1)
		sectors = mapmaker::createTestMap();

	Vector3f velocity(0, 0, 0);
	Vector3f acceleration(0, 0, -0.2);
	//player{position};
	//player.init(width/2, height/2, 20); // x, y, z
	if (MAP == 1){
		Vector3f position(5, 5, 20);
		player.init(position, velocity, acceleration, sectors[0]); // x, y, z
	}
	else{
		Vector3f position(80, 75, 20);
		player.init(position, velocity, acceleration, sectors[0]); // x, y, z
	}
}

void Game::update(std::vector<bool> keys, int mouse_x, int mouse_y){
	player.setMoveVector(keys);
	player.setMouseValues(mouse_x, mouse_y);
	//player.move(0,0);
	player.update();
}

void Game::render() {
	// empty renderer from previous iteration
    SDL_RenderClear(renderer);

    // render player & world
    render_util::renderView(renderer, &player, height_, width_);

    //player.render(renderer);
	for(auto s: sectors)
		render_util::render_map(renderer, player.x(), player.y(), player.z(), player.angle(), s->getVertices());

    // render crosshair
    SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xAA);
    SDL_RenderDrawLine(renderer, width_/2-10, height_/2, width_/2+10, height_/2);
    SDL_RenderDrawLine(renderer, width_/2, height_/2-10, width_/2, height_/2+10);

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

using namespace std;

void Game::loadMap(string mapname) {
	cout << "reading " << mapname << endl;
	
	ifstream infile(mapname);
	string line;

	while(std::getline(infile, line)) {
		switch(line.at(0)) { // read first letter in line
			case 'v': // vector

				cout << "vector-line - " << line << endl;
			break;
			case 's': // sector

				cout << "sector-line - " << line << endl;
			break;
			case 'p': // player

				cout << "player-line - " << line << endl;
			break;
		}

	}

	cout << "finished reading " << mapname << endl;
}
