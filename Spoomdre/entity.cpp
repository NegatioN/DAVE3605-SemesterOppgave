#include "entity.hpp"

Eigen::Vector3f Entity::position(){
	return position;
}
Eigen::Vector3f Entity::velocity(){
	return velocity;
}

Eigen::Vector3f Entity::accelleration(){
	return accelleration;
}

unsigned int Entity::sector(){
	return sector;
}