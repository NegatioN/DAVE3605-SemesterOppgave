#include <SDL2/SDL.h>
#include "player.hpp"

#include <iostream>

using namespace std;

SDL_Rect sprite;

float x = 150;
float y = 150;


void Player::init() {
	sprite.x = 200;
	sprite.y = 150;
	sprite.w = 5;
	sprite.h = 5;
	// coordinates for the middle of the rectangle
	x = (sprite.x + sprite.w) - sprite.w / 2;
	y = (sprite.y + sprite.h) - sprite.h / 2;
}

//Take input accelleration-vector?
void Player::move(std::vector<bool> wasd) {
    // keyboard-events
    if (wasd.at(0)) { x = x + cos(angle) * 2; y = y + sin(angle) * 2; } // W
    if (wasd.at(1)) { x = x + sin(angle) * 2; y = y - cos(angle) * 2; } // A
    if (wasd.at(2)) { x = x - cos(angle) * 2; y = y - sin(angle) * 2; } // S
    if (wasd.at(3)) { x = x - sin(angle) * 2; y = y + cos(angle) * 2; } // D
    if (wasd.at(4)) { angle = angle + 0.1; }								// K
    if (wasd.at(5)) { angle = angle - 0.1; }								// M
}

void Player::render(SDL_Renderer* renderer) {
	sprite.x = x - sprite.w / 2;
	sprite.y = y - sprite.h / 2;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, x, y, cos(angle) * 15 + x, sin(angle) * 15 + y);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color
	SDL_RenderFillRect(renderer, &sprite);
}