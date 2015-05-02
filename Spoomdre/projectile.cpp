#include <SDL2/SDL.h>
#include "projectile.hpp"
#include "gfx_util.hpp"
#include "vertex.hpp"

#include <iostream>

using namespace std;

SDL_Rect spritep;


void Projectile::init(Vector3f pos, Vector3f velo) {
	setPosition(pos);

	setVelocity(velo);
	
	spritep.w = 5;
	spritep.h = 5;
	spritep.x = 640/2 - spritep.w/2;
	spritep.y = 480/2 - spritep.h/2;
	
}

//Take input accelleration-vector?
void Projectile::update() {
    Vector3f vel = velocity();
    move(vel);

    lifeTimer++;
}

void Projectile::move(Vector3f velo) {
	Vector3f pos = position();
	pos += velo;

	std::cout << "Bullet X=" << pos(0) << " Y=" << pos(1) << " Z=" << pos(2) << std::endl;

	setPosition(pos);

	spritep.x = 640/2-spritep.w/2;
	spritep.y = 480/2-spritep.h/2;
	
}

void Projectile::render(SDL_Renderer* renderer) {
	// render small white rectangle in the center of the screen
	SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
	SDL_RenderDrawRect(renderer, &spritep);
	
	// render muzzle-flash
	if(!flashShown && flashTimer < flashLifeSpan) {
		SDL_SetRenderDrawColor(renderer, 0xFF,0x77,0x00,0xFF);

		// drawn muzzle-flash
		SDL_Rect flashrect;
		flashrect.w = 200;
		flashrect.h = 200;
		flashrect.x = 640 / 2 - flashrect.w / 2;
		flashrect.y = 480 / 2 - flashrect.h / 2;

		// render flash
		SDL_RenderFillRect(renderer, &flashrect);
		flashTimer++;

		// last flash-frame
		if(flashTimer >= flashLifeSpan) {
			flashShown = true;	
			flashTimer = 0;
		} 
	}
}


void Projectile::takeDamage(){
	
}