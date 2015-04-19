#include <SDL2/SDL.h>
#include "player.hpp"

#include <iostream>

using namespace std;

SDL_Rect sprite;


void Player::init(Vector3f pos){
	setPosition(pos);
	yaw_ = 0;
}
void Player::init(int x, int y, int z){
	yaw_ = 0;

	Vector3f vec(x,y,z);
	setPosition(vec);
	yaw_ = 0;

	sprite.w = 5;
	sprite.h = 5;
	sprite.x = x - sprite.w/2;
	sprite.y = y - sprite.h/2;
	
}

//Take input accelleration-vector?
void Player::move() {

	anglesin_ = sin(angle_);
	anglecos_ = cos(angle_);
	Vector3f vecAddition(0,0,0);
    // keyboard-events
    if (wasd_.at(0)) { vecAddition(0) += anglecos_  * 2; vecAddition(1)  += anglesin_ * 2; } 	// W
    if (wasd_.at(1)) { vecAddition(0) += anglesin_ * 2; vecAddition(1) -= anglecos_  * 2; } 	// A
    if (wasd_.at(2)) { vecAddition(0) -= anglecos_  * 2;  vecAddition(1) -= anglesin_ * 2; } 	// S
    if (wasd_.at(3)) { vecAddition(0) -= anglesin_ * 2; vecAddition(1) += anglecos_  * 2; } 	// D
    if (wasd_.at(4)) { angle_ = angle_ + 0.1; }									// right
    if (wasd_.at(5)) { angle_ = angle_ - 0.1; }									// left
    if (wasd_.at(6)) { yaw_ += 0.05; }											// up
    if (wasd_.at(7)) { yaw_ -= 0.05; }											// down

    //old position-vector += movement.
    setPosition(position() + vecAddition);

}

void Player::render(SDL_Renderer* renderer) {
	//sprite.x = x - sprite.w / 2;
	//sprite.y = y - sprite.h / 2;

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawLine(renderer, 320, 240, 320, 225);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color
	SDL_RenderFillRect(renderer, &sprite);
}