#ifndef CLASS_ENEMY_H
#define CLASS_ENEMY_H

#include <Eigen/Core>
#include "entity.hpp"
#include "gfx_util.hpp"
#include "vertex.hpp"
#include "door.hpp"
#include <math.h>
#include <SDL2/SDL.h>

using namespace Eigen;

class Enemy : public Entity {
	// constants
	float const speed_ = 0.5f;
	const double TAU=M_PI*2;

	//variables
	float angle_, anglesin_, anglecos_;
	float default_z;
	int damageCountdown = 0; //countdown for damaging player
	bool isRender = false;
	SDL_Rect renderRect;
	Entity* player_;

private:
	bool checkForWall(Vector3f& velo);	//collision-detection
	bool checkForPlayer(Vector3f& velo);
	void move(Vector3f velo);			//add velocity to position of enemy
	void takeDamage();					//deal dmg to enemy
	void render(SDL_Renderer* renderer);

public:
	Enemy(){};
	Enemy(Vector3f &pos) : Entity(pos){};
	void init(Vector3f pos);
	void init(Vector3f pos, Vector3f vel, Vector3f acc, sector* sec);

	void update();						//updates all vectors and values for enemy
	void setPlayer(Entity* p){ player_ = p; };

	float angle(){ return angle_; };
	float anglesin(){return anglesin_;};
	float anglecos(){return anglecos_;};
	float x(){ return position()(0); };
	float y(){ return position()(1); };
	float z(){ return position()(2); };
	Entity* player(){ return player_; };
	SDL_Rect getRect(){return renderRect;};

	void setRect(SDL_Rect rect){renderRect = rect;};
	void setRender(bool shouldRender){isRender = shouldRender;};
	bool getRender(){return isRender;};
};

#endif