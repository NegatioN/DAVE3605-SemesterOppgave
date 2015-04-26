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
    //top og bunn verdier for y. Brukes mer når vi skal ha høydeforskjeller på sektorer??

    float px = pos(0);
    float py = pos(1);
    float pz = pos(2);

    //draw lines for each vertex in sector
    for (int i = 0; i < vCount; i++) {
		vertex a = vertices[i];
		vertex b = vertices[0];
		if (i < vCount-1)
			b = vertices[i+1];

        int r_ = 0; int g_ = 0; int b_ = 0;
		//different wall colors
        r_ = 0xEE; g_ = 0xBB; b_ = 0x77;//Wall brown
        //r_ = 0x73; g_ = 0x73; b_ = 0x73;//dark grey
        //r_ = 0x00; g_ = 0x00; b_ = 0xFF;//blue
        //r_ = 0xFF; g_ = 0xFF; b_ = 0x00;//yellow
		//if     (i == 0){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
		// r_ = 0x00; g_ = 0xFF; b_ = 0x00;//green
		// else if(i == 3)
		// else if(i == 4){ r_ = 0xFF; g_ = 0xA5; b_ = 0x00;}//orange
		// r_ = 0xD3; g_ = 0xD3; b_ = 0xD3;//grey
        

		// x & y of sector-edge endpoints
        float vertexAx = a.x() - px;
        float vertexAy = a.y() - py;
        float vertexBx = b.x() - px;
        float vertexBy = b.y() - py;

        // Rotate around player-view
        float pcos = cos(angle);
        float psin = sin(angle);
        //player translated coordinates of vertexes
        float txA = vertexAx * psin - vertexAy * pcos;
        float tzA = vertexAx * pcos + vertexAy * psin;
        float txB = vertexBx * psin - vertexBy * pcos;
        float tzB = vertexBx * pcos + vertexBy * psin;

        // Is wall at least partially in front of player
        if(tzA <= 0 && tzB <= 0) continue;

        // If partially behind player, clip it
        if(tzA <= 0 || tzB <= 0)
        {
            float nearz = 1e-4f;
            float farz = 5;
            float nearside = 1e-5f;
            float farside = 20.f;

            // Intersection between wall and edges of player-view
            xy i1 = gfx_util::intersect(txA,tzA,txB,tzB, -nearside,nearz, -farside,farz);
            xy i2 = gfx_util::intersect(txA,tzA,txB,tzB,  nearside,nearz,  farside,farz);
            if(tzA < nearz) { if(i1.y > 0) { txA = i1.x; tzA = i1.y; } else { txA = i2.x; tzA = i2.y; } }
            if(tzB < nearz) { if(i1.y > 0) { txB = i1.x; tzB = i1.y; } else { txB = i2.x; tzB = i2.y; } }
        }

        // Perspective transformation
        float xscale1 = hfov / tzA;
        float yscale1 = vfov / tzA;    
        int x1 = W/2 - (int)(txA * xscale1);
        float xscale2 = hfov / tzB;
        float yscale2 = vfov / tzB;    
        int x2 = W/2 - (int)(txB * xscale2);

		// Only render if it's visible (doesn't render the backside of walls)
        if(x1 >= x2) continue; // Only render if it's visible


        // Ceiling&floor-height relative to player
        float yceil  = ceiling_height_  - pz;
        float yfloor = floor_height_ - pz;

        float nbrCeil=0;
        float nbrFloor=0;

        sector* neighbour = getWallNeighbour(a, b);
        door* door_ = getWallDoor(a,b);
        if (neighbour != NULL)
        {
            nbrCeil  = neighbour->ceiling()  - pz;
            nbrFloor = neighbour->floor() - pz;
        }

        // Project ceiling and floor heights to screen coordinates
        int y1Ceil = H / 2 - (int) ((yceil + tzA * yaw) * yscale1);
        int y1Floor = H / 2 - (int) ((yfloor + tzA * yaw) * yscale1);
        int y2Ceil = H / 2 - (int) ((yceil + tzB * yaw) * yscale2);
        int y2Floor = H / 2 - (int) ((yfloor + tzB * yaw) * yscale2);
        
        /* The same for the neighboring sector */
        int nbrY1Ceil = H/2 - (int)((nbrCeil+ tzA * yaw) * yscale1);
        int nbrY1Floor = H/2 - (int)((nbrFloor + tzA * yaw) * yscale1);
        int nbrY2Ceil = H/2 - (int)((nbrCeil + tzB * yaw) * yscale2);
        int nbrY2Floor = H/2 - (int)((nbrFloor + tzB * yaw) * yscale2);

        // Render the wall. 
        int beginx = std::max(x1, 0), endx = std::min(x2, W-1);
        for(int x = beginx; x <= endx; ++x)
        {
            int top = win[x].top;
            int bottom = win[x].bottom;

            //Paint corners black
            if (x == beginx || x == endx){
                r_ = 5; g_ = 5; b_ = 5;
            }
            else {
                r_ = 0xEE/getId(); g_ = 0xBB; b_ = 0x77;//Wall brown
            }

            // Calculate the Z coordinate for this point. (Only used for lighting.) 
            int z_ = ((x - x1) * (tzB-tzA) / (x2-x1) + tzA) * 8;
            int shade = (z_ - 16) / 4; // calculated from the Z-distance

            // Acquire the Y coordinates for our ceiling & floor for this X coordinate. 
            int yCeiling = (x - x1) * (y2Ceil-y1Ceil) / (x2-x1) + y1Ceil;// top
            int yFloor = (x - x1) * (y2Floor-y1Floor) / (x2-x1) + y1Floor;// bottom
            
            
            /* Is there another sector behind this edge? */


            if(neighbour != NULL)
            {
                //Find their floor and ceiling
                //int nya = 1;
                int nbrYCeil = (x - x1) * (nbrY2Ceil-nbrY1Ceil) / (x2-x1) + nbrY1Ceil;
                int nbrYFloor = (x - x1) * (nbrY2Floor-nbrY1Floor) / (x2-x1) + nbrY1Floor;
                nbrYCeil = gfx_util::clamp(nbrYCeil, top,bottom);   //clamp ceiling of neighbour to our POV
                nbrYFloor = gfx_util::clamp(nbrYFloor, top,bottom); //clamp floor of neighbour to our POV

                // If our ceiling is higher than their ceiling, render upper wall                 
                render_util::drawVLine(renderer, x, top, nbrYCeil-1, r_, g_, b_, shade);       // Between our and their ceiling

                // If our floor is lower than their floor, render bottom wall 
                render_util::drawVLine(renderer,x, nbrYFloor+1, bottom, r_, g_, b_, shade);         // Between their and our floor

                //std::cout << "Sector=" << neighbour->getId() << " top=" << top << " bottom=" << bottom << std::endl;
                win[x].top = gfx_util::clamp(std::max(yCeiling, nbrYCeil), top, H-1);    // Shrink the remaining window below these ceilings
                win[x].bottom = gfx_util::clamp(std::min(yFloor, nbrYFloor), 0, bottom); // Shrink the remaining window above these floors
            
            }
            
            else{
                
                render_util::drawVLine(renderer, x, top, bottom, r_, g_, b_, shade);
            }
            
            


            //Draw floor and ceiling
            unsigned roofColor = 0x99/getId();
            if(yCeiling > top )
                render_util::drawVLine(renderer, x, top, yCeiling, roofColor, roofColor, roofColor, 1);
            if(yFloor < bottom )
                render_util::drawVLine(renderer, x, yFloor, bottom, 0x66, 0x33, 0x00, 1);

        }
    }
}

