#include "sector.hpp"

sector::sector(int id, int floor_height, int ceiling_height) : id_{id}, floor_height_{floor_height}, ceiling_height_{ceiling_height} {

};

void sector::addVertex(vertex* v){
	vertices.push_back(v);
	vCount++;
}

//Calculate neighbouring sectors, based on this sector's vertices
void sector::findNeighbours(){};

void sector::render(SDL_Renderer* renderer){
	for (int i = 0; i < vCount; i++) {
		vertex* a = vertices[i];
		vertex* b = vertices[i+1];
		SDL_RenderDrawLine(renderer, a->x(), a->y(), b->x() ,b->y());
	}
};
