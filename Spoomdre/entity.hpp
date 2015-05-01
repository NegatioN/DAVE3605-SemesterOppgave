#ifndef CLASS_ENTITY_H
#define CLASS_ENTITY_H

#include <Eigen/Core>
#include "sector.hpp"


using namespace Eigen;
//Abstract class for entities. Meaning "Player", "Mob", "Moose"
//should this extend properties? "Position_Vector", "Velocity_vector", "Moveable"
class sector;
class Entity{

//float x_, y_, z_; //coordinates for entity
Vector3f position_, velocity_, acceleration_, startpos_; //(math)vectors of floats of length = 3
sector* sector_;				//sector of entity
sector* startsector_;

public:
	Entity(){};
	//TODO create override constructor with start-position
	Entity(Vector3f pos){
		position_ = pos;
	};
	Entity(Vector3f pos, Vector3f vel, Vector3f acc){
		position_ = pos;
		velocity_ = vel;
		acceleration_ = acc;
	};
	virtual void update()=0;
	virtual void move(Vector3f velo)=0;

	Vector3f& position(){ return position_;};				//return position-vector
	Vector3f velocity(){return velocity_;};					//return velocity-vector
	Vector3f accelleration(){return acceleration_;}; 		//return accelleration-vector
	sector* getSector(){return sector_;};					//return current sector
	Vector3f& getStartPos(){return startpos_;};				//return startpos, for respawn
	sector* getStartSector(){return startsector_;}; 		//return startsector, for respawn 
	void setPosition(Vector3f pos){position_ = pos;};		//sets position-vector
	void setStartPos(Vector3f pos){startpos_ = pos;};
	void setVelocity(Vector3f vel){velocity_ = vel;};
	void setAcceleration(Vector3f acc){acceleration_ = acc;};	
	void setSector(sector* sec){ sector_ = sec;};
	void setStartSector(sector* sec){startsector_ = sec;};

};

#endif