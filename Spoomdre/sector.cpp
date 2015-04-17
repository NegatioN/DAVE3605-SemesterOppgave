#include "sector.hpp"

sector::sector(int id, int floor_height, int ceiling_height) : id_{id}, floor_height_{floor_height}, ceiling_height_{ceiling_height} {

};

void sector::addVertex(vertex* v){
	//vertices.pushback(v);
}

//Calculate neighbouring sectors, based on this sector's vertices
void sector::findNeighbours(){};

void sector::render(){};
