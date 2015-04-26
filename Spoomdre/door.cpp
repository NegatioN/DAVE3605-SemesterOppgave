#include "door.hpp"

door::door(vertex a, vertex b, bool locked) : door_a{a},door_b{b}, door_locked{locked}{
};

bool door::checkPoints(vertex a, vertex b){
	if(!(a == getDoorA()) && !(a == getDoorB()))
		return false;
	if(!(b == getDoorA()) && !(b == getDoorB()))
		return false;
	return true;
}

void door::setDoorLocked()
{
	door_locked = !door_locked;
}