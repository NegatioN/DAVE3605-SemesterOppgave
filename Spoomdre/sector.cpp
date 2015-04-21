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

//Calculate neighbouring sectors, based on this sector's vertices
void sector::findNeighbours(){};

void sector::render(SDL_Renderer* renderer, SDL_Texture * texture, float px, float py, float pz, float angle, float yaw){
	//pixels on screen
    // Uint32 * pixels = new Uint32[640 * 480];
    // memset(pixels, 255, 640 * 480 * sizeof(Uint32));

    int ytop[W], ybottom[W]; 
    for(unsigned x=0; x<W; ++x) {ybottom[x] = H-1; ytop[x] = 0;}

    for (int i = 0; i < vCount; i++) {
		vertex a = vertices[i];
		vertex b = vertices[0];
		if (i < vCount-1)
			b = vertices[i+1];

		/* Calculate 
		float txa = a.x()-px, tya = a.y()-py;
		float txb = b.x()-px, tyb = b.y()-py;

		float tza = txa*cos(angle) + tya*sin(angle);
		float tzb = txb*cos(angle) + tyb*sin(angle);
			  txa = txa*sin(angle) - tya*cos(angle);
			  txb = txb*sin(angle) - tyb*cos(angle);*/

	    //SDL_SetRenderDrawColor(renderer, 0x00, 0x77, 0xFF, 0xFF); // map-color, Blue/green-ish
		//SDL_RenderDrawLine(renderer, 320-txa, 240-tza, 320-txb , 240-tzb); // render map
		//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color, Yellow
        int r_ = 0; int g_ = 0; int b_ = 0;
		//different wall colors
		if     (i == 0){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
		else if(i == 1){ r_ = 0x00; g_ = 0xFF; b_ = 0x00;}//green
		else if(i == 2){ r_ = 0x00; g_ = 0x00; b_ = 0xFF;}//blue
		else if(i == 3){ r_ = 0xFF; g_ = 0xFF; b_ = 0x00;}//yellow
		else if(i == 4){ r_ = 0xFF; g_ = 0xA5; b_ = 0x00;}//orange
		else if(i == 5){ r_ = 0xD3; g_ = 0xD3; b_ = 0xD3;}//grey
		else if(i == 6){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
		else if(i == 7){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
		else if(i == 8){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
		else if(i == 9){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
		else if(i == 10){ r_ = 0xFF; g_ = 0x00; b_ = 0x00;}//red
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

        // Render wall
		/*SDL_RenderDrawLine(renderer, x1, y1a, x2, y2a);
		SDL_RenderDrawLine(renderer, x1, y1b, x2, y2b);
		SDL_RenderDrawLine(renderer, x1, y1a, x1, y1b);
		SDL_RenderDrawLine(renderer, x2, y2a, x2, y2b);*/
        
        // Render the wall. 
        int beginx = x1, endx = x2;
        for(int x = beginx; x <= endx; ++x)
        {
            // Calculate the Z coordinate for this point. (Only used for lighting.) 
            //int z = ((x - x1) * (tz2-tz1) / (x2-x1) + tz1) * 8;
            // Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. 
            int ya = (x - x1) * (y2a-y1a) / (x2-x1) + y1a;//, cya = gfx_util::clamp(ya, ytop[x],ybottom[x]); // top
            int yb = (x - x1) * (y2b-y1b) / (x2-x1) + y1b;//, cyb = gfx_util::clamp(yb, ytop[x],ybottom[x]); // bottom

            // int ya = H / 2 - (int) ((yceil + tz1 * yaw) * yscale1);
            // int yb = H / 2 - (int) ((yfloor + tz1 * yaw) * yscale1);
            
            // Render ceiling: everything above this sector's ceiling height. 
            //drawline(renderer, pixels, x, x, ya, ya-H, 2,0x00,0xFFFFFF,0x0000FF);
            // Render floor: everything below this sector's floor height. 
            //drawline(renderer, pixels, x, x, yb, yb + H, 1,0xAA,0xFFFFFF,0x0000FF);

            // Is there another sector behind this edge? 
            /*if(neighbor >= 0)
            {
                /* Same for _their_ floor and ceiling */
                //int nya = (x - x1) * (ny2a-ny1a) / (x2-x1) + ny1a, cnya = gfx_util::clamp(nya, ytop[x],ybottom[x]);
               // int nyb = (x - x1) * (ny2b-ny1b) / (x2-x1) + ny1b, cnyb = gfx_util::clamp(nyb, ytop[x],ybottom[x]);
                /* If our ceiling is higher than their ceiling, render upper wall */
                //unsigned r1 = 0x010101 * (255-z), r2 = 0x040007 * (31-z/8);
                //drawline(x, cya, cnya-1, 0, x==x1||x==x2 ? 0 : r1, 0); // Between our and their ceiling
                //ytop[x] = gfx_util::clamp(max(cya, cnya), ytop[x], H-1);   // Shrink the remaining window below these ceilings
                /* If our floor is lower than their floor, render bottom wall */
               // vline(x, cnyb+1, cyb, 0, x==x1||x==x2 ? 0 : r2, 0); // Between their and our floor
              //  ybottom[x] = gfx_util::clamp(min(cyb, cnyb), 0, ybottom[x]); // Shrink the remaining window above these floors
            //}
            //else
            //{
                /* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
                //unsigned r = 0x010101 * (255-z);
            //drawline(renderer, texture, x, x, ya, yb, 0,0x0000FF,0xFFFFFF,0x0000FF);
            //copi pixels into window
            //SDL_UpdateTexture(texture, NULL, pixels, 640 * sizeof(Uint32));
            drawline(renderer, NULL, x, x, ya, yb, 0,r_,g_,b_);
            
        }

	} 
    //delete[] pixels;
};
/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void sector::drawline(SDL_Renderer* renderer, Uint32 * pixels, int x1, int x2, int y1,int y2, int type, int red, int green, int blue)
{
    /*if(type == 0)//vegg
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    else if(type == 1)//gulv
        SDL_SetRenderDrawColor(renderer, 0x00, 0x22, 0x22, 0x22);
    else if(type == 2)//tak
        SDL_SetRenderDrawColor(renderer, 0xFF, 0x77, 0x77, 0x77);*/
    y1 = gfx_util::clamp(y1, 0, H-1);
    y2 = gfx_util::clamp(y2, 0, H-1);

    SDL_SetRenderDrawColor(renderer,0xF4, 0xA4, 0x60, 0xFF); //gulv
    SDL_RenderDrawLine(renderer, x1, 480, x2, y2);
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x77, 0x77, 0x77);//tak
    SDL_RenderDrawLine(renderer, x1, y1, x2, 0);
    SDL_SetRenderDrawColor(renderer, red, green, blue, 0xFF);//vegg
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

    /*for(int i = y1;  i < y2 ; i++){
        int index = i*640+x1;
        pixels[index] = 0xFF;
        //if(i < y1)
        //    pixels[index] = 0xFF;
        //else if( y1 <= i && i < y2)
        //    pixels[index] = top;
        //else
        //    pixels[index] = 0x7A;
    }*/

     /*
     delete[] pixels;
    SDL_DestroyTexture(texture);
     */

    /*forsøk med drawpoint
    for(int i = y1;  i < y2 ; i++){
        SDL_RenderDrawPoint(renderer, x1, i);
    }*/


    /*
    y1 = gfx_util::clamp(y1, 0, H-1);
    y2 = gfx_util::clamp(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = middle;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = middle;
        pix[y2*W+x] = bottom;
    }*/
    //frosøk med metode vist i video
    /*int *pix = (int*) surface->pixels;
    y1 = gfx_util::clamp(y1, 0, H-1);
    y2 = gfx_util::clamp(y2, 0, H-1);
    if(y2 == y1)
        pix[y1*W+x] = mid;
    else if(y2 > y1)
    {
        pix[y1*W+x] = top;
        for(int y=y1+1; y<y2; ++y) pix[y*W+x] = mid;
        pix[y2*W+x] = bot;
    }*/
    //SDL_RenderDrawLine(renderer, x, y1, x2, y2);
}
