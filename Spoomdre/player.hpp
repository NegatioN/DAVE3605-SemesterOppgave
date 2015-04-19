#ifndef CLASS_PLAYER_H
#define CLASS_PLAYER_H

#include <vector>
#include "entity.hpp"
#include <Eigen/Core>

//represents the player and everything related
//should probably contain the user-input in some way.
class Player : public Entity {
	float angle_, anglesin_, anglecos_, yaw_;
	unsigned int sector;
	std::vector<bool> wasd_;

public:
	Player(){};
	Player(Vector3f &pos) : Entity(pos){};
	void init(Vector3f pos);
	void init(int x, int y, int z);
	void move();
	void render(SDL_Renderer* renderer);

	void setMoveVector(std::vector<bool> &wasd){wasd_ = wasd;}

	float angle(){ return angle_; };
	float yaw() { return yaw_; }
	float x(){ return position()(0); };
	float y(){ return position()(1); };
	float z(){ return position()(2); }

};


#endif