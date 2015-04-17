#ifndef CLASS_PLAYER_H
#define CLASS_PLAYER_H

#include <vector>
//represents the player and everything related
//should probably contain the user-input in some way.
class Player { //} : public Entity {
	float angle, anglesin, anglecos, yaw;
	unsigned int sector;

public:
	void init();
	void move(std::vector<bool> wasd);
	void render(SDL_Renderer* renderer);

};


#endif