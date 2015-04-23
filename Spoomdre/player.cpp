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
	BODYHEIGHT = 4; // can walk over everything <= 15 (20-4)
	yaw_ = 0;
}

//Take input accelleration-vector?
void Player::update() {
	bool isFalling = false;
	bool isJumping = false;
	bool isCrouching = false;
	
	anglesin_ = sin(angle_);
	anglecos_ = cos(angle_);

	Vector3f vecAddition(0,0,0);

	if(z() > default_z)
		isFalling = true;
	else
		setVelocity(vecAddition); //set velocity (0,0,0). No sliding movement

	std::cout << "Player isFalling=" << isFalling << " x=" << x() << " y=" << y() << " z=" << z() << std::endl;

	if(isFalling){
		Vector3f fallingVelo = velocity();
		move(fallingVelo);
		fallingVelo += accelleration();	//gravity
		setVelocity(fallingVelo);
	}else{


	    // keyboard-events
	    if (wasd_.at(0)) { vecAddition(0) += anglecos_  * speed_; vecAddition(1)  += anglesin_ * speed_; } 	// W
	    if (wasd_.at(1)) { vecAddition(0) += anglesin_ * speed_; vecAddition(1) -= anglecos_  * speed_; } 	// A
	    if (wasd_.at(2)) { vecAddition(0) -= anglecos_  * speed_; vecAddition(1) -= anglesin_ * speed_; } 	// S
	    if (wasd_.at(3)) { vecAddition(0) -= anglesin_ * speed_; vecAddition(1) += anglecos_  * speed_; } 	// D
	    if (wasd_.at(4)) { angle_ += 0.1; }									// right
	    if (wasd_.at(5)) { angle_ -= 0.1; }									// left
	    if (wasd_.at(6)) { yaw_ -= 0.1; }											// up
	    if (wasd_.at(7)) { yaw_ += 0.1; }											// down
	    if (wasd_.at(8)) { isCrouching = true;}									//Crouch, Z-axis
	    if (wasd_.at(9)) { isJumping = true;} 
	    if (wasd_.at(10)) { shootProjectile(); }

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

		if(isJumping)
			jump(vel);
		crouchMove(isCrouching);
	}
	// update and remove (if appropriate) projectiles if any exists
	if(projectiles.size() > 0) {
		projectileCountdown--;
		for(Projectile* p : projectiles) 
			p->update();
			
		removeDeadProjectiles();
	}
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
        	bool canPass = true;
			sector* n = getSector()->getWallNeighbour(a, b);
			if (n != NULL)
			{
				float hole_low  = n < 0 ?  9e9 : n->floor();
            	float hole_high = n < 0 ? -9e9 : min(getSector()->ceiling(),  n->ceiling());

 				if(hole_high > z()   && hole_low  < (z()-BODYHEIGHT) )
            	{
		       		//set default camera-height on sector-change
				    velo(2) = n->floor() - getSector()->floor(); 
				    default_z += velo(2);
				    setSector(n);
				    canPass = false;
            	}
			}
			
			if (canPass)
			{		
				//Bumps into a wall! Slide along the wall. 
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
	//if lower than highlimit, and player not crouching

	if(z() < default_z && !isCrouch){
		//to avoid triggering isFalling by going over default_z
		Vector3f pos = position();
		pos += crouch;
		float dz = pos(2) - default_z;
		if(pos(2) >= default_z)
			crouch(2) -= (pos(2) - default_z); //subtracts z-overflow. sets to default_z

		move(crouch);
	}
	//if higher than lowlimit, and player crouching
	else if(z() >= (default_z - 8) && isCrouch)
		move(-crouch);
}

void Player::jump(Vector3f& velo){
	velo(2) = 8;
	setVelocity(velo);

	Vector3f pos = position();
	pos(2) = default_z + 0.02; //make Z one higher than default to trigger falling-check.

	setPosition(pos);
	
}


void Player::move(Vector3f velo) {
	Vector3f pos = position();
	pos += velo;
	setPosition(pos);
}


void Player::shootProjectile() {
	if(projectiles.size() < 1) {
		projectileCountdown = 0;
	}
	if(projectileCountdown < 1) {
		Projectile* proj = new Projectile();
		Vector3f pos = position();
		proj->init(pos, angle_);
		projectiles.push_back(proj);
		
		projectileCountdown = projectileCooldown;

		std::cout << "projectile shot()" << std::endl;
	}
}

void Player::removeDeadProjectiles() {
	for(int i = 0; i < projectiles.size(); i++) {
		if(projectiles.at(i)->isDead()) {
			Projectile* p = projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);
			delete p;
			i--;
			std::cout << "projectile removed()" << std::endl;
		}
	}
}

void Player::render(SDL_Renderer* renderer) {
	//std::cout << "Player x=" << x() << " y=" << y() << " z=" << z() << std::endl;
	//std::cout << getSector()->getId() << std::endl;

	std::vector<sector*> visibleSectors = getSector()->getNeighbours();
	visibleSectors.push_back(getSector());
	for (sector* s: visibleSectors)
		s->render(renderer, x(), y(), z(), angle(), yaw());
	
	// Renders projectiles
	for(Projectile* p : projectiles)
		p->render(renderer);
}