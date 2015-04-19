#ifndef CLASS_PLAYER_H
#define CLASS_PLAYER_H

#include <vector>

//represents the player and everything related
//should probably contain the user-input in some way.
class Player { //} : public Entity {
	float angle_, anglesin, anglecos, yaw_;
	float x_;
	float y_;
	float z_;
	unsigned int sector;

public:
	void init(int x, int y, int z);
	void move(std::vector<bool> wasd);
	void render(SDL_Renderer* renderer);

	float angle(){ return angle_; };
	float yaw() { return yaw_; }
	float x(){ return x_; };
	float y(){ return y_; };
	float z(){ return z_; }

};


#endif