#ifndef CLASS_PROJECTILE_H
#define CLASS_PROJECTILE_H

#include <vector>
#include "entity.hpp"
#include <Eigen/Core>
#include <math.h>


class Projectile : public Entity {
	// life of the muzzle-flash
	bool flashShown = false;
	int flashTimer = 0;
	int flashLifeSpan = 15;

	// life of the projectile itself
	int lifeTimer = 0;
	int lifeSpan = 200;
	float angle_, anglesin_, anglecos_;
	
public:
	Projectile(){};
	Projectile(Vector3f &pos) : Entity(pos){};
	void init(Vector3f pos, float angle);
	void update();
	void move(Vector3f velo);
	void render(SDL_Renderer* renderer);

	bool isDead() { return lifeTimer > lifeSpan; };

	float angle(){ return angle_; };
	float x(){ return position()(0); };
	float y(){ return position()(1); };
	float z(){ return position()(2); }

};


#endif