#ifndef CLASS_RENDER_UTIL_H
#define CLASS_RENDER_UTIL_H

#include "linedef.hpp"
#include <SDL2/SDL.h>
#include "gfx_util.hpp"
#include <stdio.h>
#include <vector>

class render_util{
public:
	//static void drawVLine(SDL_Renderer* renderer, Linedef line, float height, float width, int red, int green, int blue, int shade);
	static void render_map(SDL_Renderer* renderer, float px, float py, float pz, float angle, std::vector<vertex> vertices);
	static void drawVLine(SDL_Renderer* renderer, int x1, int y1,int y2, int red, int green, int blue, int shade);
};


#endif