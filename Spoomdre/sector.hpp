#ifndef CLASS_SECTOR_H
#define CLASS_SECTOR_H

#include "vertex.hpp"
#include <SDL2/SDL.h>
#include <vector>

class sector{

//ID of sector, to identify neighbours
int id_;

float floor_height_;
float ceiling_height_;
//Floor + ceiling texturesz

//Number of vertexes in the sector (4 for cubical sector)
int vCount;

//All vertexes in the sector
std::vector<vertex> vertices;

//Id of all neighbouring sectors
std::vector<int> neighbours;

public:
	sector(int id_, float floor_height, float ceiling_height);

	void addVertex(vertex v);

	//Calculate neighbouring sectors, based on this sector's vertices
	void findNeighbours();
	void render(SDL_Renderer* renderer);

	int getVertexCount() { return vCount; };
	int getId() { return id_; };

};

#endif