#ifndef CLASS_ENEMY_H
#define CLASS_ENEMY_H

#include <Eigen/Core>
#include "entity.hpp"

using namespace Eigen;

//Abstract class for entities. Meaning "Player", "Mob", "Moose"
//should this extend properties? "Position_Vector", "Velocity_vector", "Moveable"
class Enemy : public Entity {

	float angle_, anglesin_, anglecos_;
	float default_z;
	//sector * sector_; -> is in entity 

	//bool isFalling = false;

	float const speed_ = 1.5f;

	float const BODYHEIGHT = 10; //size of player
	float const KNEEHEIGHT = (BODYHEIGHT/2);

	// list of projectiles (i.e bullets)
	//std::vector<Projectile*> projectiles;
	// variables for cooldown between each projectile-shoot
	//int projectileCooldown = 50;
	//int projectileCountdown = 0;

public:
	Enemy(){};
	Enemy(Vector3f &pos) : Entity(pos){};
	void init(Vector3f pos);
	void init(Vector3f pos, Vector3f vel, Vector3f acc, sector* sec);

	void update();						//updates all vectors and values for player
	void move(Vector3f velo);			//add velocity to position of player
	void render(SDL_Renderer* renderer);
	
	//void shootProjectile();
	//void removeDeadProjectiles();

	float angle(){ return angle_; };
	float anglesin(){return anglesin_;};
	float anglecos(){return anglecos_;};
	float x(){ return position()(0); };
	float y(){ return position()(1); };
	float z(){ return position()(2); };
};

#endif