#include <SDL2/SDL.h>
#include "player.hpp"

#include <iostream>

using namespace std;

SDL_Rect sprite;

int x;
int y;

void Player::init() {
	sprite.x = 200;
	sprite.y = 150;
	sprite.w = 20;
	sprite.h = 20;
	// coordinates for the middle of the rectangle
	x = (sprite.x + sprite.w) - sprite.w / 2;
	y = (sprite.y + sprite.h) - sprite.h / 2;
}

//Take input accelleration-vector?
void Player::move(std::vector<bool> wasd) {
    // keyboard-events
	if(wasd.at(0)) y-=5;	// W
	if(wasd.at(1)) x-=5;	// A
	if(wasd.at(2)) y+=5;	// S
	if(wasd.at(3)) x+=5;	// D
}

void Player::render(SDL_Renderer* renderer) {
	sprite.x = x - sprite.w / 2;
	sprite.y = y - sprite.h / 2;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color
	SDL_RenderDrawRect(renderer, &sprite);
}