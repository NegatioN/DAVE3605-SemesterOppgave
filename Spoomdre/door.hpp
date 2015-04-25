#ifndef CLASS_DOOR_H
#define CLASS_DOOR_H

#include "vertex.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <Eigen/Core>

class door{

bool door_locked;

//coordinates for door
vertex door_a, door_b;

public:
	door(vertex a, vertex b, bool locked);

	bool checkPoints(vertex a, vertex b);
	
	vertex getDoorA(){ return door_a; };
	vertex getDoorB(){ return door_b; };
	bool doorLocked(){ return door_locked; };
};

#endif