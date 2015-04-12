#ifndef CLASS_GAME_UTIL_H
#define CLASS_GAME_UTIL_H


//External Dependencies
#include <SDL2/SDL.h>
#include <stdio.h>
#include <cstdlib>



class GameUtil{

LTimer fpsTimer;
fpsTimer.start();
std::stringstream timeText; //Text to show up when we render fps on screen
int countedFrames = 0; 		//overflow etterhvert?



public:
	void fpsCounter();				//renders an fps-counter on the screen for benchmarking
};


#endif