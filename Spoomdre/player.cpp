#include <SDL2/SDL.h>
#include "player.hpp"
#include "gfx_util.hpp"
#include "vertex.hpp"

#include <iostream>

using namespace std;

SDL_Rect sprite;


void Player::init(Vector3f pos, Vector3f vel, Vector3f acc, sector* sec){
	setPosition(pos);
	setVelocity(vel);
	setAcceleration(acc);
	setSector(sec);
	default_z = sec->floor() + 10;
	yaw_ = 0;
}

//Take input accelleration-vector?
void Player::update() {
	
	anglesin_ = sin(angle_);
	anglecos_ = cos(angle_);
	Vector3f vecAddition(0,0,0);

	bool isJumping = false;
	bool isCrouching = false;
    // keyboard-events
    if (wasd_.at(0)) { vecAddition(0) += anglecos_  * 2; vecAddition(1)  += anglesin_ * 2; } 	// W
    if (wasd_.at(1)) { vecAddition(0) += anglesin_ * 2; vecAddition(1) -= anglecos_  * 2; } 	// A
    if (wasd_.at(2)) { vecAddition(0) -= anglecos_  * 2;  vecAddition(1) -= anglesin_ * 2; } 	// S
    if (wasd_.at(3)) { vecAddition(0) -= anglesin_ * 2; vecAddition(1) += anglecos_  * 2; } 	// D
    if (wasd_.at(4)) { angle_ += 0.1; }									// right
    if (wasd_.at(5)) { angle_ -= 0.1; }									// left
    if (wasd_.at(6)) { yaw_ -= 0.1; }											// up
    if (wasd_.at(7)) { yaw_ += 0.1; }											// down
    if (wasd_.at(8)) { isCrouching = true;}
    //if (wasd_.at(8)) { vecAddition(2) -= 0.9;}else{vecAddition(2) += 0.9;}			//Crouch, Z-axis

    // change angle and yaw if the mouse have moved
	if(mouse_x != 0) angle_ = mouse_x * 0.015f;
	if(mouse_y != 0) yaw_ = -gfx_util::clamp(-mouse_y * 0.023f, -5, 5);

    // set moving to true if movement-key is pressed
    bool pushing = false;
    if(wasd_.at(0) || wasd_.at(1) || wasd_.at(2) || wasd_.at(3))
    	pushing = true;

	float accel = pushing ? 0.4 : 0.2;

    Vector3f vel = velocity();
    //Vector3f crouchVelocity = velocity();
    vel(0) = vel(0) * (1 - accel) + vecAddition(0) * accel;
    vel(1) = vel(1) * (1 - accel) + vecAddition(1) * accel;
    //crouchVelocity(2) += vecAddition(2);

    //std::cout << "Velocity x=" << vel(0) << " y=" << vel(1) << " z=" << crouchVelocity(2) << std::endl;

    // set moving to true if movement-key is pressed
    bool moving = false;
    if(pushing)
    	moving = true;

	if(moving) {
	    //Is the player hitting a wall?
	    checkForWall(vel);

	    move(vel);
	}

	crouchMove(isCrouching);
}

bool Player::checkForWall(Vector3f& velo){
	//float px, float py, float& dx, float& dy
	//Vector3f position = position();

	std::vector<vertex> vertices = getSector()->getVertices();
	std::vector<sector*> neighbours = getSector()->getNeighbours();

	// Check if the player is about to cross one of the sector's edges 
    for(int i = 0; i < vertices.size(); ++i){

        vertex a = vertices[i]; 
        vertex b = vertices[i+1];
	    
	    //Loop around for last corner
	    if (i == vertices.size()-1) b = vertices[0];

        if( gfx_util::intersectBox(x(), y(), x()+velo(0),y()+velo(1), a.x(), a.y(), b.x(), b.y()) && 
            gfx_util::pointSide(x()+velo(0), y()+velo(1), a.x(), a.y(), b.x(), b.y()) < 0)
        { 
			bool wall = true;
			for (sector* n: neighbours)
				if (n->containsVertices(a, b)){ 

 				    //set default camera-height on sector-change
				    velo(2) = n->floor() - getSector()->floor(); 
				    default_z += velo(2);

					wall = false;
				    setSector(n);
				}

			if(wall)
			{	//Bumps into a wall! Slide along the wall. 
				// This formula is from Wikipedia article "vector projection". 
				float xd = b.x() - a.x(), yd = b.y() - a.y();
				velo(0) = xd * (velo(0)*xd + yd*velo(1)) / (xd*xd + yd*yd);
				velo(1) = yd * (velo(0)*xd + yd*velo(1)) / (xd*xd + yd*yd);
			}
		}
    }
}

void Player::crouchMove(bool isCrouch){
	Vector3f crouch(0,0,0.9);
	//we need to modify default_z when moving up/down on z-plane
	//if lower than highlimit, and movement positive (move up)
	if(z() < default_z && !isCrouch)
		move(crouch);
	//if higher than lowlimit, and movement negative (move down)
	else if(z() > (default_z - 8) && isCrouch)
		move(-crouch);
}
/*
void Player::jump(Vector3f& velo){
	velo(2) = 15;
}
*/

void Player::move(Vector3f velo) {
	Vector3f pos = position();
	pos += velo;

	setPosition(pos);
}

void Player::render(SDL_Renderer* renderer) {
	//std::cout << "Player x=" << x() << " y=" << y() << " z=" << z() << std::endl;
	//std::cout << getSector()->getId() << std::endl;
	getSector()->render(renderer, x(), y(), z(), angle(), yaw());
}