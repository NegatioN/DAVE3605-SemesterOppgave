#ifndef CLASS_GAME_H
#define CLASS_GAME_H

#include "entity.hpp"


//represents the player and everything related
//should probably contain the user-input in some way.
class Player : public Entity {

public:
	void move() override;

};


#endif