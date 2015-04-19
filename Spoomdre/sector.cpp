#include "sector.hpp"
#include "gfx_util.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

sector::sector(int id, float floor_height, float ceiling_height) : id_{id}, floor_height_{floor_height}, ceiling_height_{ceiling_height} {

};

void sector::addVertex(vertex v){
	vertices.push_back(v);
	vCount++;
}

//Calculate neighbouring sectors, based on this sector's vertices
void sector::findNeighbours(){};

int H = 480; // window-height
int W = 640; // window-width

float hfov = 0.73f*H;  		// Horizontal fov (Field of Vision)
float vfov = 0.2f*H;    	// Vertical fov (Field of Vision)

void sector::render(SDL_Renderer* renderer,float px, float py, float pz, float angle, float yaw){
	for (int i = 0; i < vCount; i++) {
		vertex a = vertices[i];
		vertex b = vertices[0];
		if (i < vCount-1)
			b = vertices[i+1];

		// Calculate 
		float txa = a.x()-px, tya = a.y()-py;
		float txb = b.x()-px, tyb = b.y()-py;

		float tza = txa*cos(angle) + tya*sin(angle);
		float tzb = txb*cos(angle) + tyb*sin(angle);
			  txa = txa*sin(angle) - tya*cos(angle);
			  txb = txb*sin(angle) - tyb*cos(angle);

	    //SDL_SetRenderDrawColor(renderer, 0x00, 0x77, 0xFF, 0xFF); // map-color, Blue/green-ish
		//SDL_RenderDrawLine(renderer, 320-txa, 240-tza, 320-txb , 240-tzb); // render map
		//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color, Yellow

		// different wall colors
		if     (i == 0) SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		else if(i == 1) SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
		else if(i == 2) SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0xFF, 0xFF);
		else if(i == 3) SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
		else if(i == 4) SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
		else if(i == 5) SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
		else if(i == 6) SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
		else if(i == 7) SDL_SetRenderDrawColor(renderer, 0x77, 0x77, 0xFF, 0xFF);
		else if(i == 8) SDL_SetRenderDrawColor(renderer, 0x77, 0xFF, 0x77, 0xFF);
		else if(i == 9) SDL_SetRenderDrawColor(renderer, 0xFF, 0x77, 0x77, 0xFF);
		else if(i == 10)SDL_SetRenderDrawColor(renderer, 0x77, 0x00, 0xFF, 0xFF);
		else 			SDL_SetRenderDrawColor(renderer, 0xFF, 0x77, 0x00, 0xFF);


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

        // Render wall
		SDL_RenderDrawLine(renderer, x1, y1a, x2, y2a);
		SDL_RenderDrawLine(renderer, x1, y1b, x2, y2b);
		SDL_RenderDrawLine(renderer, x1, y1a, x1, y1b);
		SDL_RenderDrawLine(renderer, x2, y2a, x2, y2b);
	} 
};
