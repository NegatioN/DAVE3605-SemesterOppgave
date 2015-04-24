#include "sector.hpp"
#include "gfx_util.hpp"

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

sector* sector::getWallNeighbour(vertex v1, vertex v2){
    for (sector* n : neighbours)
        if(n->containsVertices(v1,v2))
            return n;
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
        float vx1 = a.x() - px;
        float vy1 = a.y() - py;
        float vx2 = b.x() - px;
        float vy2 = b.y() - py;

        // Rotate around player-view
        float pcos = cos(angle);
        float psin = sin(angle);
        float tx1 = vx1 * psin - vy1 * pcos;
        float tz1 = vx1 * pcos + vy1 * psin;
        float tx2 = vx2 * psin - vy2 * pcos;
        float tz2 = vx2 * pcos + vy2 * psin;

        // Is wall at least partially in front of player
        if(tz1 <= 0 && tz2 <= 0) continue;

        // If partially behind player, clip it
        if(tz1 <= 0 || tz2 <= 0)
        {
            float nearz = 1e-4f;
            float farz = 5;
            float nearside = 1e-5f;
            float farside = 20.f;

            // Intersection between wall and edges of player-view
            xy i1 = gfx_util::intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside,farz);
            xy i2 = gfx_util::intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside,farz);
            if(tz1 < nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
            if(tz2 < nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
        }

        // Perspective transformation
        float xscale1 = hfov / tz1;
        float yscale1 = vfov / tz1;    
        int x1 = W/2 - (int)(tx1 * xscale1);
        float xscale2 = hfov / tz2;
        float yscale2 = vfov / tz2;    
        int x2 = W/2 - (int)(tx2 * xscale2);

        // setLeft(x1);
        // setRight(x2);

		// Only render if it's visible (doesn't render the backside of walls)
        if(x1 >= x2) continue; // Only render if it's visible


        // Ceiling&floor-height relative to player
        float yceil  = ceiling_height_  - pz;
        float yfloor = floor_height_ - pz;

        float nyceil=0;
        float nyfloor=0;

        sector* neighbour = getWallNeighbour(a, b);
        if (neighbour != NULL)
        {
            nyceil  = neighbour->ceiling()  - pz;
            nyfloor = neighbour->floor() - pz;
        }

        // Project ceiling and floor heights to screen coordinates
        int y1a = H / 2 - (int) ((yceil + tz1 * yaw) * yscale1);
        int y1b = H / 2 - (int) ((yfloor + tz1 * yaw) * yscale1);
        int y2a = H / 2 - (int) ((yceil + tz2 * yaw) * yscale2);
        int y2b = H / 2 - (int) ((yfloor + tz2 * yaw) * yscale2);
        
        /* The same for the neighboring sector */
        int ny1a = H/2 - (int)((nyceil+ tz1 * yaw) * yscale1);
        int ny1b = H/2 - (int)((nyfloor + tz1 * yaw) * yscale1);
        int ny2a = H/2 - (int)((nyceil + tz2 * yaw) * yscale2);
        int ny2b = H/2 - (int)((nyfloor + tz2 * yaw) * yscale2);

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
            int z_ = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
            int shade = (z_ - 16) / 4; // calculated from the Z-distance

            // Acquire the Y coordinates for our ceiling & floor for this X coordinate. 
            int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;// top
            int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;// bottom
            
            /* Is there another sector behind this edge? */
            if(neighbour != NULL)
            {
                //Find their floor and ceiling
                int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a;
                int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b;
                int cnya = gfx_util::clamp(nya, top,bottom);
                int cnyb = gfx_util::clamp(nyb, top,bottom);

                /* If our ceiling is higher than their ceiling, render upper wall */                
                drawline(renderer, x, top, cnya-1, r_, g_, b_, shade);       // Between our and their ceiling

                /* If our floor is lower than their floor, render bottom wall */
                drawline(renderer,x, cnyb+1, bottom, r_, g_, b_, shade);         // Between their and our floor

                win[x].top = gfx_util::clamp(std::max(ya, cnya), top, H-1);    // Shrink the remaining window below these ceilings
                win[x].bottom = gfx_util::clamp(std::min(yb, cnyb), 0, bottom); // Shrink the remaining window above these floors
            
            }
            else{
                drawline(renderer, x, top, bottom, r_, g_, b_, shade);
            }

            //Draw floor and ceiling
            unsigned roofColor = 0x99/getId();
            if(ya > top )
                drawline(renderer, x, top, ya, roofColor, roofColor, roofColor, 1);
            if(yb < bottom )
                drawline(renderer, x, yb, bottom, 0x66, 0x33, 0x00, 1);

        }
    }
}



//Temporary method for showing a top-down view on screen.
void sector::render_map(SDL_Renderer* renderer, float px, float py, float pz, float angle){
    
    int yOffset = -100; // displaces map by a given y
    int xOffset = 150;  // displaces map by a give x

    // Render player on map
    SDL_Rect prect;
    prect.w = 5; prect.h = 5;
    prect.x = (320+xOffset) - prect.w / 2; prect.y = (240+yOffset) - prect.h / 2;

    SDL_SetRenderDrawColor(renderer, 0x55, 0xFF, 0x55, 0xFF); // map-color, Blue/green-ish
    SDL_RenderDrawLine(renderer, 320 + xOffset, 240 + yOffset, 320 + xOffset, 232 + yOffset); // render map 
    SDL_SetRenderDrawColor(renderer, 0xBB, 0xBB, 0xBB, 0xFF); // map-color, Blue/green-ish
    SDL_RenderFillRect(renderer, &prect); // render map 

    // Render map
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

        SDL_SetRenderDrawColor(renderer, 0x00, 0x77, 0xFF, 0xFF); // map-color, Blue/green-ish
        SDL_RenderDrawLine(renderer, 320-txa + xOffset, 240-tza + yOffset, 320-txb + xOffset, 240-tzb + yOffset); // render map
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color, Yellow
    }
}


/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void sector::drawline(SDL_Renderer* renderer, int x1, int y1,int y2, int red, int green, int blue, int shade)
{
    y1 = gfx_util::clamp(y1, 0, H-1);
    y2 = gfx_util::clamp(y2, 0, H-1);

    // if calculated shade (color - shade) is under the threshold, set the color as the threshold
    SDL_SetRenderDrawColor(renderer, (red - shade < red / 4) ? red / 4 : red - shade, (green - shade < green / 4) ? green / 4 : green - shade, (blue - shade < blue / 4) ? blue / 4 : blue - shade, 0xFF);//vegg
    SDL_RenderDrawLine(renderer, x1, y1, x1, y2);

    //Borders?
    SDL_SetRenderDrawColor(renderer, 5, 5, 5, 0.5f);
    SDL_RenderDrawPoint(renderer, x1, y1);
    SDL_RenderDrawPoint(renderer, x1, y2);
}
