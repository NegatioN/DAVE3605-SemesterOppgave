#ifndef CLASS_GAME_H
#define CLASS_GAME_H

//External Dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
//internal dependencies
//#include "game_util.hpp"


//Defines the underlaying rendering-process
class Game{

	int height_, width_;

	SDL_Window* window = NULL; 			//Window to render to
	//SDL_Surface* screenSurface = NULL; 	//surface of window
	SDL_Renderer* renderer = NULL; 		//renderer renders

	SDL_Texture * texture = NULL;

	SDL_Surface* surface = NULL;

	void makeRenderer();					//simply creates the SDL_Surface

public:

	//Game(int height, int width);
	void initialize(int height, int width);//, KeyboardHandler* keyboard); //initialize the screen and surface
	void update(std::vector<bool> keys, int mouse_x, int mouse_y);					//updates the surface
	void render();
	void terminate();				//terminate screen
	void wait(int seconds);			//pause render for x seconds
	
	void loadMap(std::string mapname);	// Loads map from a txt-file

};


#endif