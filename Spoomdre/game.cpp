#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "sector.hpp"
#include "vertex.hpp"
#include "mapmaker.hpp"
#include "render_util.hpp"

#include <sstream>
#include <fstream>

Player player;
std::vector<Enemy*> enemies;
std::vector<sector*> sectors;
std::vector<SDL_Texture*> textures;
SDL_Rect rect;

int MAP = 0;

//get window surface
void Game::makeRenderer(){
	//renderer = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	SDL_Texture* wallTexture = IMG_LoadTexture(renderer, "textures/Brick_Texture.png");
	SDL_Texture* enemyTexture = IMG_LoadTexture(renderer, "textures/Enemy_Texture.png");
	SDL_Texture* gunTexture = IMG_LoadTexture(renderer, "textures/Handgun_Texture.png");
	SDL_Texture* doorTexture = IMG_LoadTexture(renderer, "textures/Door_Texture.png");
	SDL_Texture* gunflashTexture = IMG_LoadTexture(renderer, "textures/Gunflash_Texture_Large.png");
	textures.push_back(wallTexture);
	textures.push_back(enemyTexture);
	textures.push_back(gunTexture);
	textures.push_back(doorTexture);
	textures.push_back(gunflashTexture);
}

void Game::initialize(int height, int width) {
	//INIT SDL
	if(SDL_Init( SDL_INIT_VIDEO) < 0){
		printf("SDL Could not initialize! SDL_ERROR: %s\n",
			SDL_GetError());
	}else{
	//Create Window
		window = SDL_CreateWindow("Spoomdre", 
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

	//init gunSpace on screen
	int gunW = (width_/5);
	int gunH = (height_/5)*2;
	int gunY = (height_-gunH);
	int gunX = (width_/2)+(gunW/2);
	gunSpace = {gunX,gunY,gunW, gunH};

	
	int flashW = (width_/7);
	int flashH = (height_/7);
	int flashY = (height_- flashH) - 150;
	int flashX = (width_/2)+(flashW/2) - 20;
	gunFlash = {flashX, flashY, flashW, flashH};

	if(MAP == 0)
		sectors = mapmaker::createMap();
	else if(MAP == 1)
		sectors = mapmaker::createTestMap();

	Vector3f velocity(0, 0, 0);
	Vector3f acceleration(0, 0, -0.2);

	if (MAP == 1){
		Vector3f position(5, 5, 20);
		player.init(position, velocity, acceleration, sectors[0]); // x, y, z
	}
	else{
		Vector3f position(80, 75, 20);
		player.init(position, velocity, acceleration, sectors[0]); // x, y, z
	
		Vector3f positionE1(70, 80, 20);
		Vector3f positionE2(50, 50, 20);
		Vector3f positionE3(85, 90, 20);
		static Enemy enemy1;
		static Enemy enemy2;
		// static Enemy enemy3;
		enemy1.init(positionE1, velocity, acceleration, sectors[0]);
		enemy2.init(positionE2, velocity, acceleration, sectors[0]);
		// enemy3.init(positionE3, velocity, acceleration, sectors[0]);
		enemies.push_back(&enemy1);
		enemies.push_back(&enemy2);
		// enemies.push_back(&enemy3);

		std::cout << "Enemy coordinates: " << enemy1.x() << " " << enemy1.y() << " " << enemy1.z() << std::endl;
		//std::cout << "InitP: " << en->x() << " " << en->y() << " " << en->z() << std::endl;
	}
}

void Game::update(std::vector<bool> keys, int mouse_x, int mouse_y){
	player.setMoveVector(keys);
	player.setMouseValues(mouse_x, mouse_y);
	for(Enemy* e : enemies){
		if (player.getSector()->getId() == e->getSector()->getId())
		{
			e->setPlayer(&player);
		}
		e->update();
	}

	if(keys.at(10) && flashCountdown == 0){ // pressed shoot
		player.shoot(&enemies);
		flashCountdown = flash_time;
	}

	player.update();
}

void Game::render() {
	// empty renderer from previous iteration
    SDL_RenderClear(renderer);

    // render world from player's POV
    render_util::renderView(renderer, textures, &player, enemies, height_, width_);

 	//render map
	for(auto s : sectors)
		render_util::render_map(renderer, &player, s->getVertices(), height_, width_);

    // render crosshair
    SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xAA);
    SDL_RenderDrawLine(renderer, width_/2-10, height_/2, width_/2+10, height_/2);
    SDL_RenderDrawLine(renderer, width_/2, height_/2-10, width_/2, height_/2+10);

    //if player just pressed shoot - render gunflash
    if(flashCountdown > 0){
		if(flashCountdown > 150)
			SDL_RenderCopy(renderer, textures.at(4), NULL, &gunFlash);
		flashCountdown--;
	}

    //render gun-model
    SDL_RenderCopy(renderer, textures.at(2), NULL, &gunSpace);

    //render hp-bar
    render_util::render_player_hp(renderer, &player, height_, width_);


    //Render to screen
	SDL_SetRenderDrawColor(renderer, 0,0,0,0); // background-color
    SDL_RenderPresent(renderer); // draw


}

void Game::terminate(){
	//Destroy renderer
	SDL_DestroyRenderer(renderer);

	//Destroy textures
	for (SDL_Texture* t : textures)
		SDL_DestroyTexture(t);
	

	//Destroy window
	SDL_DestroyWindow(window);

	//quit SDL Subsystems
	SDL_Quit();

	if(MAP == 0){
		//delete all sectors
		for(sector* a : sectors)
			delete a;
	}
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
