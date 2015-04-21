#ifndef CLASS_ENTITY_H
#define CLASS_ENTITY_H

#include <Eigen/Core>


using namespace Eigen;
//Abstract class for entities. Meaning "Player", "Mob", "Moose"
//should this extend properties? "Position_Vector", "Velocity_vector", "Moveable"
class Entity{

//float x_, y_, z_; //coordinates for entity
Vector3f position_, velocity_, acceleration_; //(math)vectors of floats of length = 3
unsigned int sector_;				//sector of entity


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
	virtual void move(float dx, float dy)=0;
	Vector3f& position(){ return position_;};			//return position-vector
	Vector3f& velocity(){return velocity_;};				//return velocity-vector
	Vector3f& acceleration(){return acceleration_;}; 	//return accelleration-vector
	unsigned int sector(){return sector_;};				//return sectorId
	void setPosition(Vector3f pos){position_ = pos;};	//sets position-vector
	void setVelocity(Vector3f vel){velocity_ = vel;};
	void setAcceleration(Vector3f acc){acceleration_ = acc;};	

};

#endif