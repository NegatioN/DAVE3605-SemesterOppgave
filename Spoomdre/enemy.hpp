#ifndef CLASS_ENEMY_H
#define CLASS_ENEMY_H

#include <Eigen/Core>
#include "entity.hpp"
#include "gfx_util.hpp"
#include "vertex.hpp"
#include "door.hpp"
#include <math.h>

using namespace Eigen;

//Abstract class for entities. Meaning "Player", "Mob", "Moose"
//should this extend properties? "Position_Vector", "Velocity_vector", "Moveable"
class Enemy : public Entity {

	float angle_, anglesin_, anglecos_;
	float default_z;
	//sector * sector_; -> is in entity 

	//bool isFalling = false;

	float const speed_ = 1.5f;

	float const BODYHEIGHT = 10; //size of enemy
	float const KNEEHEIGHT = (BODYHEIGHT/2);

	const double TAU=M_PI*2;

	Entity* player_;

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

	void update();						//updates all vectors and values for enemy
	void move(Vector3f velo);			//add velocity to position of enemy
	void render(SDL_Renderer* renderer);

	bool checkForWall(Vector3f& velo);	//collision-detection
	bool checkForPortal(sector* n, Vector3f& velo, vertex a, vertex b);
	bool checkForPlayer(Vector3f& velo);

	void setPlayer(Entity* p){ player_ = p; };
	
	//void shootProjectile();
	//void removeDeadProjectiles();

	float angle(){ return angle_; };
	float anglesin(){return anglesin_;};
	float anglecos(){return anglecos_;};
	float x(){ return position()(0); };
	float y(){ return position()(1); };
	float z(){ return position()(2); };
	Entity* player(){ return player_; };
};

#endif