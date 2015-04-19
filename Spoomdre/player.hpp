#ifndef CLASS_PLAYER_H
#define CLASS_PLAYER_H

#include <vector>
#include "entity.hpp"

//represents the player and everything related
//should probably contain the user-input in some way.
class Player : public Entity {
	float angle_, anglesin, anglecos, yaw_;
	float x_;
	float y_;
	float z_;
	unsigned int sector;
	std::vector<bool> wasd_;

public:
	void init(int x, int y, int z);
	void move();
	void render(SDL_Renderer* renderer);

	void setMoveVector(std::vector<bool> &wasd){wasd_ = wasd;}

	float angle(){ return angle_; };
	float yaw() { return yaw_; }
	float x(){ return x_; };
	float y(){ return y_; };
	float z(){ return z_; }

};


#endif