#ifndef CLASS_RENDER_UTIL_H
#define CLASS_RENDER_UTIL_H

#include "player.hpp"
#include "enemy.hpp"
#include "sector.hpp"
#include "vertex.hpp"
#include "door.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "gfx_util.hpp"
#include <stdio.h>
#include <vector>
#include <queue>
#include <Eigen/Core>

//the x,y parts of a sector we can see and render
struct sectorView{ sector* thisSector; int leftCropX, rightCropX, topCropY, botCropY;};
//used to render an enemy after everything else
struct enemyView {sectorView view; Enemy* enemy;}; 

class render_util{
	void renderSector(sector currentSect);
	

public:
	static void renderView(SDL_Renderer* renderer, std::vector<SDL_Texture*> textures, Player* player, std::vector<Enemy*> enemies, int screenHeight, int screenWidth);
	static void renderEnemy(SDL_Renderer* renderer, SDL_Texture* texture, sectorView* sectorV, Player* player, Enemy* enemy, int screenHeight, int screenWidth);
	//static void drawVLine(SDL_Renderer* renderer, Linedef line, float height, float width, int red, int green, int blue, int shade);
	static void render_map(SDL_Renderer* renderer, Player* player, SDL_Texture* texture, std::vector<vertex> vertices, int screenHeight, int screenWidth);
	static void drawVLine(SDL_Renderer* renderer, int x1, int y1,int y2, int red, int green, int blue, int shade, int screenHeight, int screenWidth);
	static void vLineTexture(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y1, int y2, int beginx, float wallHeight, float widthIndex, int top, int bottom);
	static void render_player_hp(SDL_Renderer* renderer, Player* player, int screenHeight, int screenWidth);
};


#endif