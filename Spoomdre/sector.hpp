#ifndef CLASS_SECTOR_H
#define CLASS_SECTOR_H

#include "vertex.hpp"
#include "door.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <Eigen/Core>

class sector{


int id_; //ID of sector, to identify neighbours
int vCount; //Number of vertexes in the sector (4 for cubical sector)
int H = 480; // window-height
int W = 640; // window-width
int texture_id; //texture id- for rendering
float floor_height_;
float ceiling_height_;
float hfov = 0.73f*H;  		// Horizontal fov (Field of Vision)
float vfov = 0.2f*H;    	// Vertical fov (Field of Vision)


std::vector<vertex> vertices; //All vertexes in the sector
std::vector<sector*> neighbours;//Id of all neighbouring sectors
std::vector<door*> doors; //all doors in this sector

public:
	sector(int id_, float floor_height, float ceiling_height);

	sector(int id_, float floor_height, float ceiling_height, std::vector<vertex> vert, int texture_);

	void addVertex(vertex v);
	void addNeighbour(sector* s);
	void addDoor(door* d);

	sector* getWallNeighbour(vertex v1, vertex v2);
	door* getWallDoor(vertex v1, vertex v2);
	bool containsVertices(vertex v1, vertex v2);
	int getVertexCount() { return vCount; };
	int getId() { return id_; };

	std::vector<vertex> getVertices(){return vertices;};
	std::vector<sector*> getNeighbours(){return neighbours;};
	std::vector<door*> getDoors(){return doors;};

	float floor(){ return floor_height_; };
	float ceiling(){ return ceiling_height_; };
	int texture(){ return texture_id; };
};

#endif