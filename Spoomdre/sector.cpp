#include "sector.hpp"

sector::sector(int id, float floor_height, float ceiling_height) : id_{id}, floor_height_{floor_height}, ceiling_height_{ceiling_height} {

};

void sector::addVertex(vertex v){
	vertices.push_back(v);
	vCount++;
}

//Calculate neighbouring sectors, based on this sector's vertices
void sector::findNeighbours(){};

void sector::render(SDL_Renderer* renderer,float px, float py, float angle){
	for (int i = 0; i < vCount; i++) {
		vertex a = vertices[i];
		vertex b = vertices[0];
		if (i < vCount-1)
			b = vertices[i+1];

		//Calculate 
		float txa = a.x()-px, tya = a.y()-py;
		float txb = b.x()-px, tyb = b.y()-py;

		float tza = txa*cos(angle) + tya*sin(angle);
		float tzb = txb*cos(angle) + tyb*sin(angle);
			  txa = txa*sin(angle) - tya*cos(angle);
			  txb = txb*sin(angle) - tyb*cos(angle);

		SDL_RenderDrawLine(renderer, 320-txa, 240-tza, 320-txb , 240-tzb);
	}
};
