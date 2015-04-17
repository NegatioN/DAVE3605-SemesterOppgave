#ifndef CLASS_GAME_H
#define CLASS_GAME_H

//External Dependencies
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
//internal dependencies
//#include "game_util.hpp"


//Defines the underlaying rendering-process
class Game{

	SDL_Window* window = NULL; 			//Window to render to
	//SDL_Surface* screenSurface = NULL; 	//surface of window
	SDL_Renderer* renderer = NULL; 		//renderer renders

	void makeRenderer();					//simply creates the SDL_Surface

public:

	//Game(int height, int width);
	void initialize(int height, int width);//, KeyboardHandler* keyboard); //initialize the screen and surface
	void update(std::vector<bool> wasd);					//updates the surface
	void render();
	void fillRect(SDL_Rect rect, int r, int g, int b);	//renders rectangle on screen
	void terminate();				//terminate screen
	void wait(int seconds);			//pause render for x seconds
	

};


#endif