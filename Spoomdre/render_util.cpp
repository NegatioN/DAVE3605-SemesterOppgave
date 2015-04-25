#include "render_util.hpp"


/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
/*
void render_util::drawVLine(SDL_Renderer* renderer, Linedef line, float height, float width, int red, int green, int blue, int shade)
{
    //y1 = gfx_util::clamp(y1, 0, height-1);
    //y2 = gfx_util::clamp(y2, 0, height-1);

    vertex left = line.left();
    vertex right = line.right();
    // if calculated shade (color - shade) is under the threshold, set the color as the threshold
    SDL_SetRenderDrawColor(renderer, (red - shade < red / 4) ? red / 4 : red - shade, (green - shade < green / 4) ? green / 4 : green - shade, (blue - shade < blue / 4) ? blue / 4 : blue - shade, 0xFF);//vegg
    SDL_RenderDrawLine(renderer, left.x(), left.y(), right.x(), right.y());

    //Borders?
    SDL_SetRenderDrawColor(renderer, 5, 5, 5, 0.5f);
    SDL_RenderDrawPoint(renderer, left.x(), left.y();
    SDL_RenderDrawPoint(renderer, left.x(), right.y());
}
*/

/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
void render_util::drawVLine(SDL_Renderer* renderer, int x1, int y1,int y2, int red, int green, int blue, int shade)
{
	int H = 480; // window-height
	int W = 640; // window-width
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


//Temporary method for showing a top-down view on screen.
void render_util::render_map(SDL_Renderer* renderer, float px, float py, float pz, float angle, std::vector<vertex> vertices){

	int vCount = vertices.size();
    
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

