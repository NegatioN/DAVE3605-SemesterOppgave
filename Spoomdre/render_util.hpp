#ifndef CLASS_RENDER_UTIL_H
#define CLASS_RENDER_UTIL_H

#include "player.hpp"
#include "enemy.hpp"
#include "sector.hpp"
#include "vertex.hpp"
#include "door.hpp"
#include <SDL2/SDL.h>
#include "gfx_util.hpp"
#include <stdio.h>
#include <vector>
#include <queue>
#include <Eigen/Core>

struct sectorView{ sector* thisSector; int leftCropX, rightCropX;};


class render_util{
	void renderSector(sector currentSect);
	

public:
	static void renderView(SDL_Renderer* renderer, SDL_Texture* texture, Player* player, std::vector<Enemy*> enemies, int screenHeight, int screenWidth);
	static void renderEnemy(SDL_Renderer* renderer, sector* currentSector, Player* player, Enemy* enemy, int screenHeight, int screenWidth);
	//static void drawVLine(SDL_Renderer* renderer, Linedef line, float height, float width, int red, int green, int blue, int shade);
	static void render_map(SDL_Renderer* renderer, Player* player, std::vector<vertex> vertices);
	static void drawVLine(SDL_Renderer* renderer, int x1, int y1,int y2, int red, int green, int blue, int shade);
	static void vLineTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y1, int y2, int top, int middle, int bottom);

};


#endif