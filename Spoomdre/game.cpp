#include "game.hpp"
#include "player.hpp"
#include "enemy.hpp"
#include "sector.hpp"
#include "vertex.hpp"
#include "mapmaker.hpp"
#include "render_util.hpp"

#include <sstream>
#include <fstream>

	//GameVariables
Player player;						//Player
std::vector<Enemy*> enemies;		//all enemies
std::vector<sector*> sectors;		//all sectors
std::vector<SDL_Texture*> textures;	//all textures

int MAP = 2;						//which map is used

//get window surface
void Game::makeRenderer(){
	//renderer = SDL_GetWindowSurface(window);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	//load textures
	SDL_Texture* wallTexture = IMG_LoadTexture(renderer, "textures/Brick_Texture.png");
	SDL_Texture* enemyTexture = IMG_LoadTexture(renderer, "textures/Enemy_Texture.png");
	SDL_Texture* gunTexture = IMG_LoadTexture(renderer, "textures/Handgun_Texture.png");
	SDL_Texture* doorTexture = IMG_LoadTexture(renderer, "textures/Door_Texture.png");
	SDL_Texture* gunflashTexture = IMG_LoadTexture(renderer, "textures/Gunflash_Texture_LargeV2.png");
	SDL_Texture* gunTextureFired = IMG_LoadTexture(renderer, "textures/Handgun_Texture_FiredV3.png");
	SDL_Texture* minimapTexture = IMG_LoadTexture(renderer, "textures/Minimap_Texture.png");
	SDL_Texture* dirtTexture = IMG_LoadTexture(renderer, "textures/Dirt_Texture.png");
	SDL_Texture* stoneWallTexture = IMG_LoadTexture(renderer, "textures/Wall_Stone_Texture.png");
	SDL_Texture* goldWallTexture = IMG_LoadTexture(renderer, "textures/Gold_Wall_Texture.png");

	//push to texture vector
	textures.push_back(wallTexture);
	textures.push_back(enemyTexture);
	textures.push_back(gunTexture);
	textures.push_back(doorTexture);
	textures.push_back(gunflashTexture);
	textures.push_back(gunTextureFired);
	textures.push_back(minimapTexture);
	textures.push_back(dirtTexture);
	textures.push_back(stoneWallTexture);
	textures.push_back(goldWallTexture);
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
	
	//init muzzleFlash of gun
	int flashW = (width_/2);
	int flashH = (height_/2);
	int flashY = (height_- flashH) - 50;
	int flashX = (width_/2)+(flashW/2) - (width_/2.66);
	gunFlash = {flashX, flashY, flashW, flashH};

	//sets size of minimap	
    background.w = width_/3.5; background.h = width_/3.5;
    background.x = (width_-100) - background.w / 2; background.y = (100) - background.h / 2;

    //create map-sectors
	if(MAP == 0)
		sectors = mapmaker::createMap();
	else if(MAP == 1)
		sectors = mapmaker::createTestMap();
	else if(MAP == 2)
		sectors = mapmaker::createShowcaseMap();

	//initiate movement/accelleration/position vectors
	Vector3f velocity(0, 0, 0);
	Vector3f acceleration(0, 0, -0.2);

	if (MAP == 1){
		Vector3f position(5, 5, 20);
		player.init(position, velocity, acceleration, sectors[0]); // x, y, z
	}
	else if (MAP == 2) {
		Vector3f position(5, 5, 20);
		player.init(position, velocity, acceleration, sectors[0]); // x, y, z

		Vector3f positionE1(80, 175, 20);
		Vector3f positionE2(60, 95, 20);
		Vector3f positionE3(60, 80, 20);
		Vector3f positionE4(60, 20, 30);
		Vector3f positionE5(85, 20, 5);
		Vector3f positionE6(95, 20, 35);

		static Enemy enemy1;
		static Enemy enemy2;
		static Enemy enemy3;
		static Enemy enemy4;
		static Enemy enemy5;
		static Enemy enemy6;
		
		enemy1.init(positionE1, velocity, acceleration, sectors[18]);
		enemy2.init(positionE2, velocity, acceleration, sectors[41]);
		enemy3.init(positionE3, velocity, acceleration, sectors[43]);
		enemy4.init(positionE4, velocity, acceleration, sectors[27]);
		enemy5.init(positionE5, velocity, acceleration, sectors[29]);
		enemy6.init(positionE6, velocity, acceleration, sectors[30]);


		enemies.push_back(&enemy1);
		enemies.push_back(&enemy2);
		enemies.push_back(&enemy3);
		enemies.push_back(&enemy4);
		enemies.push_back(&enemy5);
		enemies.push_back(&enemy6);
	}
}

/*
* Takes in user-input
* Handles all variable-updates in the gameloop.
*/
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

	if(flashCountdown > 0)
		flashCountdown--;

	player.update();
}

/*
* Simply calls all render-functions we need for each frame
*/
void Game::render() {
	// empty renderer from previous iteration
    SDL_RenderClear(renderer);

    // render world from player's POV
    render_util::renderView(renderer, textures, &player, enemies, height_, width_);

    //render minimap
    SDL_RenderCopy(renderer, textures.at(6), NULL, &background);

 	//render map
	for(auto s : sectors)
		render_util::render_map(renderer, &player, textures.at(6), s->getVertices(), height_, width_);

    // render crosshair
    SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xAA);
    SDL_RenderDrawLine(renderer, width_/2-10, height_/2, width_/2+10, height_/2);
    SDL_RenderDrawLine(renderer, width_/2, height_/2-10, width_/2, height_/2+10);

    //if player just pressed shoot - render gunflash
    if(flashCountdown > 22){ // only render the first few frames
		SDL_RenderCopy(renderer, textures.at(4), NULL, &gunFlash);
		SDL_RenderCopy(renderer, textures.at(5), NULL, &gunSpace);
	} else {
		//render gun-model
    	SDL_RenderCopy(renderer, textures.at(2), NULL, &gunSpace);
	}

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
