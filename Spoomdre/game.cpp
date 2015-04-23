#include "game.hpp"
#include "player.hpp"
#include "sector.hpp"
#include "vertex.hpp"

Player player;
std::vector<sector*> sectors;
SDL_Rect rect;

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

	createWorld();
	Vector3f position(75, 75, 20);
	Vector3f velocity(0, 0, 0);
	Vector3f acceleration(0, 0, 0);
	//player{position};
	//player.init(width/2, height/2, 20); // x, y, z
	player.init(position, velocity, acceleration, sectors[0]); // x, y, z
}

void Game::update(std::vector<bool> wasd, int mouse_x, int mouse_y){
	player.setMoveVector(wasd);
	player.setMouseValues(mouse_x, mouse_y);
	//player.move(0,0);
	player.update();
}

void Game::render() {
	// empty renderer from previous iteration
    SDL_RenderClear(renderer);

    // render player & world
    //player.render(renderer);

    player.render(renderer);
	for(auto s: sectors)
		s->render_map(renderer, player.x(), player.y(), player.z(), player.angle());

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

void Game::createWorld(){
	int id = 1;

	//Need static to save the sectors. (New causes wierd bug)
	static sector s1{id++, 10.f, 40.f}, 
				  s2{id++, 10.f, 50.f},
				  s3{id++, 10.f, 50.f};


	// vertexes for test-map
	vertex v1 = vertex{50, 50};
	vertex v2 = vertex{90, 50};
	vertex v3 = vertex{120, 75};
	vertex v4 = vertex{120, 100};
	vertex v5 = vertex{50, 100};

	vertex v6 = vertex{90, 10};
	vertex v7 = vertex{50, 10};

	vertex v8= vertex{120, 10};

	vertex v9 = vertex{120, 140};
	vertex v10= vertex{80, 140};
	vertex v11= vertex{40, 120};

	s1.addVertex(v1);
	s1.addVertex(v2);
	s1.addVertex(v3);
	s1.addVertex(v4);
	s1.addVertex(v5);

	s2.addVertex(v1);
	s2.addVertex(v7);
	s2.addVertex(v6);
	s2.addVertex(v2);

	s3.addVertex(v2);
	s3.addVertex(v6);
	s3.addVertex(v8);
	s3.addVertex(v3);


	s1.addNeighbour(&s2);
	s1.addNeighbour(&s3);
	s2.addNeighbour(&s1);
	s2.addNeighbour(&s3);
	s3.addNeighbour(&s1);
	s3.addNeighbour(&s2);

	sectors.push_back(&s1);
	sectors.push_back(&s2);
	sectors.push_back(&s3);

}
