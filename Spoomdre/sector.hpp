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


int H = 480; // window-height
int W = 640; // window-width

float hfov = 0.73f*H;  		// Horizontal fov (Field of Vision)
float vfov = 0.2f*H;    	// Vertical fov (Field of Vision)

//Number of vertexes in the sector (4 for cubical sector)
int vCount;

//All vertexes in the sector
std::vector<vertex> vertices;

//Id of all neighbouring sectors
std::vector<sector*> neighbours;

public:
	sector(int id_, float floor_height, float ceiling_height);

	void addVertex(vertex v);
	void addNeighbour(sector* s);

	void render(SDL_Renderer* renderer, float px, float py, float pz, float angle, float yaw);
	void render_map(SDL_Renderer* renderer, float px, float py, float pz, float angle);

	void drawline(SDL_Renderer* renderer, int x,int y1, int y2, int red, int green, int blue, int alpha);

	int getVertexCount() { return vCount; };
	int getId() { return id_; };

};

#endif