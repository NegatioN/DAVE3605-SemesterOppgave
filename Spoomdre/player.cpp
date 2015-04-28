#include <SDL2/SDL.h>
#include "player.hpp"
#include <iostream>

using namespace std;

SDL_Rect sprite;

bool isCrouching = false;

void Player::init(Vector3f pos, Vector3f vel, Vector3f acc, sector* sec){
	setPosition(pos);
	setVelocity(vel);
	setAcceleration(acc);
	setSector(sec);
	default_z = sec->floor() + BODYHEIGHT; 
	yaw_ = 0;
}

//Take input accelleration-vector?
void Player::update() {
	isFalling = false;
	isCrouching = false;
	bool isJumping = false;
	if(doorCountdown > 0) --doorCountdown;
	
	anglesin_ = sin(angle_);
	anglecos_ = cos(angle_);

	Vector3f vecAddition(0,0,0);

	updatePOV();

	if(z() > default_z)
		isFalling = true;
	else
		setVelocity(vecAddition); //set velocity (0,0,0). No sliding movement

	//handy debug-line
	//std::cout << "Player Sector=" << getSector()->getId() << " isFalling=" << isFalling << " x=" << x() << " y=" << y() << " z=" << z() << " default_z=" << default_z << std::endl;

	if(isFalling){
		 //Crouching while jumping. Not visible, but makes it possible to jump into small openings.
		if (keys_.at(8)) { isCrouching = true;}

		Vector3f fallingVelo = velocity();
		Vector3f pos = position();

		float maxHeight = getSector()->ceiling();
		//if player bumps against roof of sector, set z-velo to zero and z to maxHeight
		if(pos(2) + fallingVelo(2) >= maxHeight){
			//fallingVelo(2) = 0; //player no longer acends if he hits roof
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
	    if (keys_.at(11)){ if(doorCountdown == 0) checkForEvent(); }

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
			for (sector* n: neighbours){
				checkForPortal(n, velo, a, b);
			}
			//Bumps into a wall! Slide along the wall. 
			// This formula is from Wikipedia article "vector projection". 
			float xd = b.x() - a.x(), yd = b.y() - a.y();
			velo(0) = xd * (velo(0)*xd + yd*velo(1)) / (xd*xd + yd*yd);
			velo(1) = yd * (velo(0)*xd + yd*velo(1)) / (xd*xd + yd*yd);
			//std::cout << "Hopper, men treffer vegg" << std::endl;

			//will you hit slide past this wall now?
			if( (min(a.x(), b.x()) > x()+velo(0) || x()+velo(0) > max(a.x(), b.x())) && 
				(min(a.y(), b.y()) > y()+velo(1) || y()+velo(1) > max(a.y(), b.y()))  ){
				//but will you hit sector? - need test
				velo(0) = 0;
				velo(1) = 0;
			}
			return true;
		}
    }
    return false;
}

bool Player::checkForPortal(sector* n, Vector3f& velo, vertex a, vertex b){
	if (n->containsVertices(a, b)){ 
		float hole_low  = n < 0 ?  9e9 : max(getSector()->floor(), n->floor());//height of the heigest floor - gives opening
		float hole_high = n < 0 ? -9e9 : min(getSector()->ceiling(),  n->ceiling());//height of the lowest floor- gives opening
		float floor_diff = n->floor() - getSector()->floor();// height differens of sector floors
		
		//is this wall a door?
		door* door_ = n->getWallDoor(a,b);
		bool isDoorLocked = (door_ != NULL && door_->doorLocked());
		// can player walk/jump through opening?
		// std::cout << " Positions relative to sector=" << n->getId() << " kneeheight=" << KNEEHEIGHT << " floor_diff=" << floor_diff << " Hole height" << (hole_high - hole_low) << std::endl;
		//is sector changed if falling? easier to get into portals while falling(jumping)
		if(isFalling){
														//z-kneeheight 
			if(((hole_high - hole_low) >= ((isCrouching ? CROUCHHEIGHT : BODYHEIGHT)+HEADSIZE)) && (z()-KNEEHEIGHT) >= hole_low && z() <= hole_high && !isDoorLocked )
			{
				std::cout << "entered sector(FALLING)=" << n->getId() << std::endl;

		    	setSector(n);
		    	//sets default_z to floor + BodyHeight. Player will move towards this next frame
		    	default_z = getSector()->floor() + BODYHEIGHT;
		    	velo(2) = 0;	//remove extra velocity up when jumping into sector
		    	velo /= 2;
		    	setVelocity(velo);		//if we fall after sector-change we fall forward.
		    	return true;
    		}	
		}
		//is sector changed? if not falling
		else{
    		if(((hole_high - hole_low) >= ((isCrouching ? CROUCHHEIGHT : BODYHEIGHT)+HEADSIZE)) && (floor_diff <= (KNEEHEIGHT)) && (z() <= hole_high) && !isDoorLocked) 
			{
				std::cout << "entered sector=" << n->getId() << std::endl;

		    	setSector(n);
		    	//sets default_z to floor + BodyHeight. Player will move towards this next frame
		    	default_z = getSector()->floor() + BODYHEIGHT;
		    	velo /= 2;
		    	setVelocity(velo);		//if we fall after sector-change we fall forward.
		    	return true;
    		}	
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
	velo(2) = 2.5;
	setVelocity(velo);

	Vector3f pos = position();
	pos(2) = default_z + 0.1; //make Z one higher than default to trigger falling-check.

	checkForWall(velo);
	setPosition(pos);	
}


void Player::move(Vector3f velo) {
	Vector3f pos = position();
	pos += velo;
	setPosition(pos);
}

void Player::checkForEvent(){
	doorCountdown = 10;
	//all doors
	std::vector<door*> doors = getSector()->getDoors();
	//sector has door // should be has "event" (when we add more)
	if(doors.size() > 0)
	{
		door* active = NULL;
		float margin_x = 0, margin_y = 0;

		float x_, y_;
		for(door* e : doors)
		{
			vertex a = e->getDoorA();
			vertex b = e->getDoorB();

			float x_middle, y_middle;

			x_middle = (std::abs(b.x()-a.x())/2) + min(a.x(),b.x());
			y_middle = (std::abs(b.y()-a.y())/2) + min(a.y(),b.y());

			std::vector<float> closest_point = closestToEvent(a,b,x_middle,y_middle);

			float temp_x = closest_point.at(0);
			float temp_y = closest_point.at(1);

			if(temp_x <= event_radius && temp_y <= event_radius){
				if(active == NULL)
				{
					margin_x = temp_x;
					margin_y =temp_y;
					active = e;
				}
				else if(temp_x < margin_x && temp_x < margin_y)
				{
					margin_x = temp_x;
					margin_y =temp_y;
					active = e;
				}
			}
		}

		if(active != NULL)
		{
			active->setDoorLocked();
		}
	}
}

//checks which point is closest to player(a-middle-b)
std::vector<float> Player::closestToEvent(vertex a, vertex b, float middle_x, float middle_y){
	float margin_a_x, margin_a_y, margin_middle_x,margin_middle_y, margin_b_x,margin_b_y,
		total_a, total_b, total_middle;
	std:vector<float> margin;

	Vector3f pos = position();
	float x = pos(0);
	float y = pos(1);

	margin_a_x = std::abs(x - a.x());
	margin_a_y = std::abs(y - a.y());
	total_a = margin_a_x + margin_a_y;

	margin_middle_x = std::abs(x - middle_x);
	margin_middle_y = std::abs(y - middle_y);
	total_middle = margin_middle_x + margin_middle_y;

	margin_b_x = std::abs(x - b.x());
	margin_b_y = std::abs(y - b.y());
	total_b = margin_b_x + margin_b_y;

	if(total_a < total_b && total_a < total_middle)
	{
		//a is closest
		margin.push_back(margin_a_x);
		margin.push_back(margin_a_y);
	}else if(total_b < total_middle && total_b < total_a){
		//middle is closest
		margin.push_back(margin_b_x);
		margin.push_back(margin_b_y);
	}else{
		//b is closest
		margin.push_back(margin_middle_x);
		margin.push_back(margin_middle_y);
	}
	return margin;
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