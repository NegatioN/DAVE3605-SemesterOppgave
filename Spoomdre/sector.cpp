#include "sector.hpp"
#include "gfx_util.hpp"
#include "render_util.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <iostream>

sector::sector(int id, float floor_height, float ceiling_height) : id_{id}, floor_height_{floor_height}, ceiling_height_{ceiling_height} {

};

sector::sector(int id, float floor_height, float ceiling_height, std::vector<vertex> vert) : id_{id}, floor_height_{floor_height}, ceiling_height_{ceiling_height}, vertices{vert} {
    vCount = vert.size();
};

void sector::addVertex(vertex v){
	vertices.push_back(v);
	vCount++;
}

//Add neighbouring sectors
void sector::addNeighbour(sector* s){
    neighbours.push_back(s);
};

void sector::addDoor(door* d){
    doors.push_back(d);
};

sector* sector::getWallNeighbour(vertex v1, vertex v2){
    for (sector* n : neighbours)
        if(n->containsVertices(v1,v2))
            return n;
    return NULL;           
}

door* sector::getWallDoor(vertex v1, vertex v2){
    for (door* d : doors)
        if(d->checkPoints(v1,v2))
            return d;
    return NULL;           
}

bool sector::containsVertices(vertex v1, vertex v2){
    int found = 0;
    for (vertex v: vertices)
        if (v == v1 || v == v2)
            found++;
    return found == 2;
}


void sector::render(SDL_Renderer* renderer, Eigen::Vector3f pos, float angle, float yaw, window win[]){

}

