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
	isFalling = false;
	bool isJumping = false;
	bool isCrouching = false;
	
	anglesin_ = sin(angle_);
	anglecos_ = cos(angle_);

	Vector3f vecAddition(0,0,0);

	updatePOV();

	if(z() > default_z)
		isFalling = true;
	else
		setVelocity(vecAddition); //set velocity (0,0,0). No sliding movement

	//std::cout << "Player isFalling=" << isFalling << " x=" << x() << " y=" << y() << " z=" << z() << std::endl;

	if(isFalling){
		Vector3f fallingVelo = velocity();
		Vector3f pos = position();

		float maxHeight = getSector()->ceiling();
		//if player bumps against roof of sector, set z-velo to zero and z to maxHeight
		if(pos(2) + fallingVelo(2) >= maxHeight){
			fallingVelo(2) = 0; //player no longer acends if he hits roof
			pos(2) = maxHeight; // 
			setPosition(pos);
		}
		move(fallingVelo);
		fallingVelo += accelleration();	//gravity
		checkForWall(fallingVelo);
		setVelocity(fallingVelo);
	}else{


	    // keyboard-events
	    if (keys_.at(0)) { vecAddition(0) += anglecos_  * speed_; vecAddition(1)  += anglesin_ * speed_; } 	// W
	    if (keys_.at(1)) { vecAddition(0) += anglesin_ * speed_; vecAddition(1) -= anglecos_  * speed_; } 	// A
	    if (keys_.at(2)) { vecAddition(0) -= anglecos_  * speed_; vecAddition(1) -= anglesin_ * speed_; } 	// S
	    if (keys_.at(3)) { vecAddition(0) -= anglesin_ * speed_; vecAddition(1) += anglecos_  * speed_; } 	// D
	    if (keys_.at(8)) { isCrouching = true;}									//Crouch, Z-axis
	    if (keys_.at(9)) { isJumping = true; } 
	    if (keys_.at(10)) { shootProjectile(); }

	    // set moving to true if movement-key is pressed
	    bool pushing = false;
	    if(keys_.at(0) || keys_.at(1) || keys_.at(2) || keys_.at(3))
	    	pushing = true;

		float accel = pushing ? 0.4 : 0.2;

	    Vector3f vel = velocity();
	    //Vector3f crouchVelocity = velocity();
	    vel(0) = vel(0) * (1 - accel) + vecAddition(0) * accel;
	    vel(1) = vel(1) * (1 - accel) + vecAddition(1) * accel;

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

		if(isJumping){
			jump(vel);
		}
		else
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
//true, hits wall or goto next sector
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
			for (sector* n: neighbours)
				if (n->containsVertices(a, b)){ 
					//Hvis man hopper er alle tak/gulv-tester fjernet - for nå
					//ellers fungerer det som det skal
					/*
					if(velo(2) > 0){
						velo(2) = n->floor() - getSector()->floor(); 
				    	default_z += velo(2);
						setSector(n);
						std::cout << "BYTTER SECTOR" << std::endl;
						return true;
					}
					*/
 				    
					if(z() > n->floor() + 30.0f) { // if fall-distance if over 30
						std::cout << "falling " << z() << " - " << n->floor() << std::endl;
						isFalling = true;

						//set default camera-height on sector-change
				    	velo(2) = n->floor() + 10.0f; // default_z = floor + 10.0f, for some reason
				    	default_z = velo(2);
						setSector(n);
				    	return true;
					}

					float hole_low  = n < 0 ?  9e9 : n->floor();
            		float hole_high = n < 0 ? -9e9 : min(getSector()->ceiling(),  n->ceiling());

            		if((hole_high > z()   && hole_low  < (z()-BODYHEIGHT) ))
            		{
		       			//set default camera-height on sector-change
				    	velo(2) = n->floor() - getSector()->floor(); 
				    	default_z += velo(2);
				    	setSector(n);
				    	return true;
            		}	
            	}
			//Bumps into a wall! Slide along the wall. 
			// This formula is from Wikipedia article "vector projection". 
			float xd = b.x() - a.x(), yd = b.y() - a.y();
			velo(0) = xd * (velo(0)*xd + yd*velo(1)) / (xd*xd + yd*yd);
			velo(1) = yd * (velo(0)*xd + yd*velo(1)) / (xd*xd + yd*yd);	
			//std::cout << "Hopper, men treffer vegg" << std::endl;
			return true;
		}
    }
    return false;
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
	velo(2) = 4;
	setVelocity(velo);

	Vector3f pos = position(); // fungerer likt med og uten denne - kan den fjernes?
	pos(2) = default_z + 0.1; //make Z one higher than default to trigger falling-check.

	checkForWall(velo);
	setPosition(pos); // no grunn til å gjøre det sånn her?
	//move(velo);

	
}


void Player::move(Vector3f velo) {
	Vector3f pos = position();
	pos += velo;
	setPosition(pos);
}

void Player::updatePOV(){
	//Keyboard-events for POV (Yaw+angle)
    if (keys_.at(4)) { angle_ += 0.1; }		// right
    if (keys_.at(5)) { angle_ -= 0.1; }		// left
    if (keys_.at(6)) { yaw_ -= 0.1; }		// up
    if (keys_.at(7)) { yaw_ += 0.1; }		// down

    //Mouse-events for POV (Yaw+Angle)
	if(mouse_x != 0) angle_ = mouse_x * 0.015f;
	if(mouse_y != 0) yaw_ = -gfx_util::clamp(-mouse_y * 0.023f, -5, 5);
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
	int W = 640;
	int H = 480;
	sector::window windows[W];
	for(unsigned i = 0; i < W; ++i) {
        windows[i].bottom = H-1;
        windows[i].top = 0;
    }

    getSector()->render(renderer, position(), angle(), yaw(), windows);

	std::vector<sector*> visibleSectors = getSector()->getNeighbours();
	for (int i = 0; i < visibleSectors.size() ; i++){
		sector* s = visibleSectors[i];

		//Add neighbour's neighbours
		for(sector* n : s->getNeighbours())
			if (find(visibleSectors.begin(), visibleSectors.end(), n) == visibleSectors.end() && n != getSector())
				visibleSectors.push_back(n);

		//Render sector
		s->render(renderer, position(), angle(), yaw(), windows);
	}
    
	// Renders projectiles
	for(Projectile* p : projectiles)
		p->render(renderer);
}