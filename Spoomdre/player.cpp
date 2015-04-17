#include <SDL2/SDL.h>
#include "player.hpp"

#include <iostream>

using namespace std;

SDL_Rect sprite;


void Player::init(int x, int y) {
	x_ = x;
	y_ = y;

	sprite.w = 5;
	sprite.h = 5;
	sprite.x = x - sprite.w/2;
	sprite.y = y - sprite.h/2;
}

//Take input accelleration-vector?
void Player::move(std::vector<bool> wasd) {
    // keyboard-events
    if (wasd.at(0)) { x_ = x_ + cos(angle_) * 2; y_ = y_ + sin(angle_) * 2; } // W
    if (wasd.at(1)) { x_ = x_ + sin(angle_) * 2; y_ = y_ - cos(angle_) * 2; } // A
    if (wasd.at(2)) { x_ = x_ - cos(angle_) * 2; y_ = y_ - sin(angle_) * 2; } // S
    if (wasd.at(3)) { x_ = x_ - sin(angle_) * 2; y_ = y_ + cos(angle_) * 2; } // D
    if (wasd.at(4)) { angle_ = angle_ + 0.1; }								// K
    if (wasd.at(5)) { angle_ = angle_ - 0.1; }								// M
}

void Player::render(SDL_Renderer* renderer) {
	//sprite.x = x - sprite.w / 2;
	//sprite.y = y - sprite.h / 2;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, 320, 240, 320, 225);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color
	SDL_RenderFillRect(renderer, &sprite);
}