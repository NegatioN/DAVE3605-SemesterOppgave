#ifndef CLASS_ENTITY_H
#define CLASS_ENTITY_H

#include <Eigen/Core>



//Abstract class for entities. Meaning "Player", "Mob", "Moose"
//should this extend properties? "Position_Vector", "Velocity_vector", "Moveable"
class Entity{

float x_, y_, z_; //coordinates for entity
Eigen::Vector3f position, velocity, accelleration; //(math)vectors of floats of length = 3
unsigned int sector;				//sector of player


public:
	//TODO create override constructor with start-position
	virtual void move()=0;
	Eigen::Vector3f position();	//return position-vector
	Eigen::Vector3f velocity();	//return velocity-vector
	Eigen::Vector3f accelleration(); //return accelleration-vector
	unsigned int sector();		//return sectorId

};

#endif