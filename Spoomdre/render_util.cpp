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
