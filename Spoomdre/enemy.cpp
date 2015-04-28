#include "enemy.hpp"
#include <iostream>
#include <SDL2/SDL.h>

SDL_Rect enemySprite;

void Enemy::init(Vector3f pos, Vector3f vel, Vector3f acc, sector* sec){
	setPosition(pos);
	setVelocity(vel);
	setAcceleration(acc);
	setSector(sec);

	enemySprite.w = 100;
	enemySprite.h = 50;
	enemySprite.x = 10;
	enemySprite.y = 20;
}

void Enemy::update() {
	//std::cout << "yoll" << std::endl;
}

void Enemy::move(Vector3f velo) {
	Vector3f pos = position();
	pos += velo;
	setPosition(pos);
}

/*
void Player::shootProjectile() {
	if(projectiles.size() < 1) {
		projectileCountdown = 0;
	}
	if(projectileCountdown < 1) {
		Projectile* proj = new Projectile();
		Vector3f pos = position();
		proj->init(pos, angle_);
		projectiles.push_back(proj);
		
		projectileCountdown = projectileCooldown;

		std::cout << "projectile shot()" << std::endl;
	}
}

void Player::removeDeadProjectiles() {
	for(int i = 0; i < projectiles.size(); i++) {
		if(projectiles.at(i)->isDead()) {
			Projectile* p = projectiles.at(i);
			projectiles.erase(projectiles.begin() + i);
			delete p;
			i--;
			std::cout << "projectile removed()" << std::endl;
		}
	}
}
*/

void Enemy::render(SDL_Renderer* renderer) {
	//SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
	//SDL_RenderFillRect(renderer, &enemySprite);
}