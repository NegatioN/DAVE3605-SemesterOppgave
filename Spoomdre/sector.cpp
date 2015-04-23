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

bool sector::containsVertices(vertex v1, vertex v2){
    int found = 0;
    for (vertex v: vertices)
        if (v == v1 || v == v2)
            found++;
    return found == 2;
}

sector* sector::getEnteredSector(float px, float py, float dx, float dy){
    // for(int i = 0; i < vCount; ++i) {
    //     //Two vertices is a wall
    //     vertex a = vertices[i], b = vertices[i+1];
        
    //     //Loop around for last corner
    //     if (i == vCount-1) b = vertices[0];

    //     //Prints for debugging. Will be removed.
    //     // if (gfx_util::intersectBox(px, py, px+dx,py+dy, a.x(), a.y(), b.x(), b.y()))
    //     //     std::cout << "intersectBox: "<< i << std::endl; 

    //     if( gfx_util::intersectBox(px, py, px+dx,py+dy, a.x(), a.y(), b.x(), b.y()) && 
    //         gfx_util::pointSide(px+dx, py+dy, a.x(), a.y(), b.x(), b.y()) < 0)
    //     {            
    //         for (sector* n: neighbours)
    //             if (n->containsVertices(a, b))
    //                 return n;
    //     }
    // }
    // return this;
    return NULL;
}




void sector::render(SDL_Renderer* renderer, float px, float py, float pz, float angle, float yaw){

    //top og bunn verdier for y. Brukes mer når vi skal ha høydeforskjeller på sektorer??
    int ytop[W], ybottom[W]; 
    for(unsigned x=0; x<W; ++x) {ybottom[x] = H-1; ytop[x] = 0;}

    for (int i = 0; i < vCount; i++) {
		vertex a = vertices[i];
		vertex b = vertices[0];
		if (i < vCount-1)
			b = vertices[i+1];

        int r_ = 0; int g_ = 0; int b_ = 0;
		//different wall colors
		if     (i == 0){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
		else if(i == 1){ r_ = 0x00; g_ = 0xFF; b_ = 0x00;}//green
		else if(i == 2){ r_ = 0x00; g_ = 0x00; b_ = 0xFF;}//blue
		else if(i == 3){ r_ = 0xFF; g_ = 0xFF; b_ = 0x00;}//yellow
		else if(i == 4){ r_ = 0xFF; g_ = 0xA5; b_ = 0x00;}//orange
		else if(i == 5){ r_ = 0xD3; g_ = 0xD3; b_ = 0xD3;}//grey
		else if(i == 6){ r_ = 0xAA; g_ = 0x00; b_ = 0x00;}//??
		else if(i == 7){ r_ = 0x33; g_ = 0x33; b_ = 0x33;}//??
		else if(i == 8){ r_ = 0xFF; g_ = 0x00; b_ = 0xFF;}//??
		else if(i == 9){ r_ = 0xF0; g_ = 0xA0; b_ = 0x0F;}//??
		else if(i == 10){ r_ = 0xFF; g_ = 0xFF; b_ = 0xFF;}//??
		else {			r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
        

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

		// Only render if it's visible (doesn't render the backside of walls)
    	if(x1 >= x2) continue; 
        
        // Ceiling&floor-height relative to player
        float yceil  = ceiling_height_  - pz;
        float yfloor = floor_height_ - pz;

        // Project ceiling and floor heights to screen coordinates
        int y1a = H / 2 - (int) ((yceil + tz1 * yaw) * yscale1);
        int y1b = H / 2 - (int) ((yfloor + tz1 * yaw) * yscale1);
        int y2a = H / 2 - (int) ((yceil + tz2 * yaw) * yscale2);
        int y2b = H / 2 - (int) ((yfloor + tz2 * yaw) * yscale2);
        
        // Render the wall. 
        int beginx = x1, endx = x2;
        for(int x = beginx; x <= endx; ++x)
        {
            // Calculate the Z coordinate for this point. (Only used for lighting.) 
            int z_ = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
            // Acquire the Y coordinates for our ceiling & floor for this X coordinate. 
            int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;// top
            int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;// bottom

            drawline(renderer, x, ya, yb, r_, g_, b_, z_);
        }
	} 
};

//Temporary method for showing a top-down view on screen.
void sector::render_map(SDL_Renderer* renderer, float px, float py, float pz, float angle){
    
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
        SDL_RenderDrawLine(renderer, 320-txa, 240-tza, 320-txb , 240-tzb); // render map
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color, Yellow
    }
}


/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void sector::drawline(SDL_Renderer* renderer, int x1, int y1,int y2, int red, int green, int blue, int alpha)
{
    y1 = gfx_util::clamp(y1, 0, H-1);
    y2 = gfx_util::clamp(y2, 0, H-1);

    SDL_SetRenderDrawColor(renderer,0xF4, 0xA4, 0x60, 0xFF); //gulv
    SDL_RenderDrawLine(renderer, x1, 480, x1, y2);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x77, 0x77, 0x77);//tak
    SDL_RenderDrawLine(renderer, x1, y1, x1, 0);
    SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);//vegg
    SDL_RenderDrawLine(renderer, x1, y1, x1, y2);
}
