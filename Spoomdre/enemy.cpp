#include "enemy.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <cmath>
#include "player.hpp"

using namespace std;

void Enemy::init(Vector3f pos, Vector3f vel, Vector3f acc, sector* sec){
	setPosition(pos);
	setVelocity(vel);
	setAcceleration(acc);
	setSector(sec);

	angle_ = ((double)rand() / 6.2);

//	enemySprite.w = 100;
	//enemySprite.h = 50;
	//enemySprite.x = 10;
	//enemySprite.y = 20;
}

void Enemy::update() {
	Vector3f vecAddition(0,0,0);

	if(damageCountdown > 0)
		damageCountdown--;

	//is player in this sector?
	if(player() != NULL && player()->getSector()->getId() == getSector()->getId()){
		//calculate angle to point towards player
		Vector3f player_pos = player_->position();
		float xd = player_pos(0)-x();
		float yd = player_pos(1)-y();
		angle_ = std::atan2(yd,xd)*(TAU/2)/ M_PI; // 
	}

	anglesin_ = sin(angle_);
	anglecos_ = cos(angle_);

	vecAddition(0) += anglecos_  * speed_;
	vecAddition(1)  += anglesin_ * speed_;
	Vector3f vel = velocity();

	vel(0) = vel(0) * (1 - 0.2) + vecAddition(0) * 0.2;
	vel(1) = vel(1) * (1 - 0.2) + vecAddition(1) * 0.2;
	
	if(!checkForPlayer(vel))
		checkForWall(vel);
	move(vel);
	
}

//can handle dmg to player
bool Enemy::checkForPlayer(Vector3f& velo){
	//hits player
	if(player_ != NULL && player()->getSector()->getId() == getSector()->getId())
	{	
		Vector3f player_pos = player_->position();
		//stands next to player
		float diff_x = std::abs(x() - player_pos(0)), diff_y = std::abs(y() - player_pos(1));
		if((diff_x > -1 && diff_x <= 1) &&
		   (diff_y > -1 && diff_y <= 1) ){
		   	if(damageCountdown == 0){
		   		std::cout << "TREFFER PLAYER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		   		player_->takeDamage();
		   		damageCountdown = 50;
		   	}
			velo(0) = 0;
			velo(1) = 0;
			return true; 
		}
	}
	return false;
}

//true, hits wall or goto next sector
bool Enemy::checkForWall(Vector3f& velo){
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
			// for (sector* n: neighbours){
			// 	if(checkForPortal(n, velo, a, b)) //did we hit a portal?
			// 		return true;
			// }

			//hits wall, uses normal vector(wall) and direction to calculate new direction and angle
			float xd = b.x() - a.x(), yd = b.y() - a.y();

			//creates 2 2D vectors for normal and direction -> calulates reflection(2D)
			Vector2f normal(xd, yd);
			Vector2f new_dir(velo(0),velo(1));
			Vector2f dir; 
			dir = 2*(new_dir.dot(normal))* normal - new_dir;

			//finds angle of reflection vector
			float vector_angle = std::atan2(dir(1),dir(0));

			//sets new direction
			velo(0) = dir(0);
			velo(1) = dir(1);
			angle_ = vector_angle;

			//will you slide past this wall?
			if( (min(a.x(), b.x()) > x()+velo(0) || x()+velo(0) > max(a.x(), b.x())) && 
				(min(a.y(), b.y()) > y()+velo(1) || y()+velo(1) > max(a.y(), b.y()))  ){
				//but will you hit new sector? - need test
				velo(0) = 0;
				velo(1) = 0;
			}

			
			return true;
		}
    }
    return false;
}
//should enemy pass through sector?
bool Enemy::checkForPortal(sector* n, Vector3f& velo, vertex a, vertex b){
	if (n->containsVertices(a, b)){ 
		float hole_low  = n < 0 ?  9e9 : max(getSector()->floor(), n->floor());//height of the heigest floor - gives opening
		float hole_high = n < 0 ? -9e9 : min(getSector()->ceiling(),  n->ceiling());//height of the lowest floor- gives opening
		float floor_diff = n->floor() - getSector()->floor();// height differens of sector floors
		
		//is this wall a door? and if so, is it locked?
		door* door_ = n->getWallDoor(a,b);
		bool isDoorLocked = (door_ != NULL && door_->doorLocked());
		// can player walk/jump through opening?
		// std::cout << " Positions relative to sector=" << n->getId() << " kneeheight=" << KNEEHEIGHT << " floor_diff=" << floor_diff << " Hole height" << (hole_high - hole_low) << std::endl;
  //   	if(((hole_high - hole_low) >= ((isCrouching ? CROUCHHEIGHT : BODYHEIGHT)+HEADSIZE)) && (z() <= hole_high) && !isDoorLocked &&
  //   		((!isFalling && floor_diff <= KNEEHEIGHT) || (isFalling && z()-KNEEHEIGHT >= hole_low))) 
		// {
		// 	std::cout << "entered sector=" << n->getId() << std::endl;
		//    	setSector(n);
		// 	move(velo);

		//    	//sets default_z to floor + BodyHeight. Player will move towards this next frame
		//    	default_z = getSector()->floor() + BODYHEIGHT;
		//    	//velo /= 2;
		//    	setVelocity(velo);		//if we fall after sector-change we fall forward.
	 //    	return true;
  //  		}	
	}
	return false;
}

void Enemy::move(Vector3f velo) {
	Vector3f pos = position();
	pos += velo;
	setPosition(pos);
}

void Enemy::render(SDL_Renderer* renderer) {
	//SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
	//SDL_RenderFillRect(renderer, &enemySprite);
}


void Enemy::takeDamage(){
	//kill enemy
}