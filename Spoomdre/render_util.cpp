#include "render_util.hpp"
#include <iostream>


// WELCOME TO THE MATRIX
void render_util::renderView(SDL_Renderer* renderer, std::vector<SDL_Texture*> textures, Player* player, std::vector<Enemy*> enemies, int screenHeight, int screenWidth){
	float hfov = 0.73f*screenHeight; 		// Horizontal fov (Field of Vision)
	float vfov = 0.2f*screenHeight;    		// Vertical fov (Field of Vision)


	SDL_Texture* wallTexture = textures[0];
	SDL_Texture* enemyTexture = textures[1];
	SDL_Texture* doorTexture = textures[3];
	SDL_Texture* dirtTexture = textures[7];
	SDL_Texture* stoneWallTexture = textures[8];
	
	//keeps track of y-coord for neighbour-sector
	int ytop[screenWidth], ybottom[screenWidth];
	for(int i = 0; i < screenWidth; ++i){ ybottom[i] = screenHeight-1; ytop[i] = 0;}

	//get sector of player
	sector* playerSector = player->getSector();
	//define view of first sector (whole screen)
	sectorView playerSectorView{playerSector, 0, screenWidth-1, 0, screenHeight-1};

	std::queue<sectorView> sectorRenderQueue;
	//std::queue<sector*> sectorRenderQueue;
	sectorRenderQueue.push(playerSectorView);
	//Sectors for enemies for rendering sectors after views
	std::vector<enemyView> enemyViews;

	int NumSectors = 64;
	int renderedSectors[NumSectors];
	for(unsigned n=0; n<NumSectors; ++n) renderedSectors[n] = 0;


	while(!sectorRenderQueue.empty()){
		sectorView currentSectorView = sectorRenderQueue.front(); //get front-element from queue
		sector* currentSector = currentSectorView.thisSector;
		sectorRenderQueue.pop();	//remove front-element from queue

		///START RENDER SECTOR
		
		std::vector<vertex> vertices = currentSector->getVertices();	//verticies in sector
		int vertexCount = vertices.size();	//number of verticies in sector

		//If render int == 1, sector is still rendering. If it's 2, it's finished rendering.
    	if(renderedSectors[currentSector->getId()-1] & 0x21) continue; 
			++renderedSectors[currentSector->getId()-1];

		//draw lines for each vertex in sector
		for (int i = 0; i < vertexCount; i++) {
			vertex a = vertices[i]; vertex b = vertices[0];
			
			if (i < vertexCount-1)
				b = vertices[i+1];


			// x & y of sector-edge endpoints
	        float vertexAx = a.x() - player->x(); float vertexAy = a.y() - player->y();
	        float vertexBx = b.x() - player->x(); float vertexBy = b.y() - player->y();

	        float psin = player->anglesin(); float pcos = player->anglecos();
	      	//player translated coordinates of vertexes
	        float txA = vertexAx * psin - vertexAy * pcos; float tzA = vertexAx * pcos + vertexAy * psin;
	        float txB = vertexBx * psin - vertexBy * pcos; float tzB = vertexBx * pcos + vertexBy * psin;

            // Is wall at least partially in front of player
        	if(tzA <= 0 && tzB <= 0) continue;

        	// If partially behind player, clip it
	        if(tzA <= 0 || tzB <= 0)
	        {
	            float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;

	            // Intersection between wall and edges of player-view
	            xy i1 = gfx_util::intersect(txA,tzA,txB,tzB, -nearside,nearz, -farside,farz);
	            xy i2 = gfx_util::intersect(txA,tzA,txB,tzB,  nearside,nearz,  farside,farz);
	            if(tzA < nearz) { if(i1.y > 0) { txA = i1.x; tzA = i1.y; } else { txA = i2.x; tzA = i2.y; } }
	            if(tzB < nearz) { if(i1.y > 0) { txB = i1.x; tzB = i1.y; } else { txB = i2.x; tzB = i2.y; } }
	        }
            // Perspective transformation
	        float xscale1 = hfov / tzA; float yscale1 = vfov / tzA;  
	       	float xscale2 = hfov / tzB; float yscale2 = vfov / tzB; 
	       
	        int x1 = screenWidth / 2 - (int)(txA * xscale1); 
	        int x2 = screenWidth / 2 - (int)(txB * xscale2);


	        float dx = b.x()-a.x(), dy = b.y()-a.y();
	        float wallLength = sqrt(dx*dx + dy*dy);
			float playerWallLength = abs(x1-x2);
	        float distanceIndex = playerWallLength/wallLength/20;
	        /*
	        if (wallLength == 25){
				std::cout << "WallLength: " << wallLength << " PWL: " << playerWallLength << " Index: " << distanceIndex << std::endl;
				std::cout << "x1: " << x1 << "x2: " << x2 << std::endl;
			}
			*/

    		// Only render if it's visible (doesn't render the backside of walls)
        	if(x1 >= x2 || x2 < currentSectorView.leftCropX || x1 > currentSectorView.rightCropX) continue;

        	float playerZ = player->z();
	        // Ceiling&floor-height relative to player
        	float yceil  = currentSector->ceiling()  - playerZ;
        	float yfloor = currentSector->floor() - playerZ;

        	float nbrCeil = 0; float nbrFloor = 0;

        	// Are current vertexes shared between neighbour-sector?
        	sector* neighbour = currentSector->getWallNeighbour(a, b);
        	//is this wall a door?
        	door* door_ = currentSector->getWallDoor(a,b);
        	bool isDoorLocked = (door_ != NULL && door_->doorLocked());
	        if (neighbour != NULL)
	        {
	            nbrCeil  = neighbour->ceiling()  - playerZ;
	            nbrFloor = neighbour->floor() - playerZ;
	        }
	        float yaw = player->yaw();

	        // Project ceiling and floor heights to screen coordinates
	        int y1Ceil  = screenHeight / 2 - (int) ((yceil + tzA * yaw) * yscale1);
	        int y1Floor = screenHeight / 2 - (int) ((yfloor + tzA * yaw) * yscale1);
	        int y2Ceil  = screenHeight / 2 - (int) ((yceil + tzB * yaw) * yscale2);
	        int y2Floor = screenHeight / 2 - (int) ((yfloor + tzB * yaw) * yscale2);
	        
	        // The same for the neighboring sector
	        int nbrY1Ceil  = screenHeight / 2 - (int)((nbrCeil+ tzA * yaw) * yscale1);
	        int nbrY1Floor = screenHeight / 2 - (int)((nbrFloor + tzA * yaw) * yscale1);
	        int nbrY2Ceil  = screenHeight / 2 - (int)((nbrCeil + tzB * yaw) * yscale2);
	        int nbrY2Floor = screenHeight / 2 - (int)((nbrFloor + tzB * yaw) * yscale2);

            // Render the wall. 
        	int beginx = std::max(x1, currentSectorView.leftCropX);
        	int endx = std::min(x2, currentSectorView.rightCropX);
        	int wallHeight = 0;
        	//find apporx limits of y-values to render mob in
        	int minTopY = screenHeight-1;
        	int maxBotY = 0;
	        for(int x = beginx; x <= endx; ++x)
	        {
	            int top = ytop[x];
	            int bottom = ybottom[x];

	            if(top < minTopY)
	            	minTopY = top;
	            if(bottom > maxBotY)
	            	maxBotY = bottom;

	            int r_, g_, b_;
	            //Paint corners black
	            r_ = 0xEE/3; g_ = 0xBB; b_ = 0x77;//Wall brown

	            // Calculate the Z coordinate for this point. (Only used for lighting.) 
	            int z_ = ((x - x1) * (tzB-tzA) / (x2-x1) + tzA) * 3;
	            int alpha = gfx_util::clamp(255-z_, 63, 255); //(z_ - 16) / 4; // calculated from the Z-distance

	            // Acquire the Y coordinates for our ceiling & floor for this X coordinate. 
	            int yCeiling = (x - x1) * (y2Ceil-y1Ceil) / (x2-x1) + y1Ceil;// top
	            int yFloor = (x - x1) * (y2Floor-y1Floor) / (x2-x1) + y1Floor;// bottom
				int cropYCeiling = gfx_util::clamp(yCeiling, top, bottom);
                int cropYFloor = gfx_util::clamp(yFloor, top, bottom);

				float wallHeight = yFloor-yCeiling;

                // Draw floor and ceiling
                unsigned roofColor = 0x99;
                drawVLine(renderer, x, top, cropYCeiling-1, roofColor, roofColor, roofColor, 1, screenHeight, screenWidth);
                drawVLine(renderer, x, cropYFloor+1, bottom, 0x66, 0x33, 0x00, 1, screenHeight, screenWidth);
				// vLineTexture(renderer, texture, x, top, cropYCeiling-1, 0,0,0);
				// vLineTexture(renderer, texture, x, cropYFloor+1, bottom, 0,0,0);

	            // Another sector behind this edge?
	            if(neighbour != NULL)
	            {
	                //Find their floor and ceiling
	                int nbrYCeil = (x - x1) * (nbrY2Ceil-nbrY1Ceil) / (x2-x1) + nbrY1Ceil;
	                int nbrYFloor = (x - x1) * (nbrY2Floor-nbrY1Floor) / (x2-x1) + nbrY1Floor;
					nbrYCeil = gfx_util::clamp(nbrYCeil, top, bottom);   //clamp ceiling of neighbour to our POV
					nbrYFloor = gfx_util::clamp(nbrYFloor, top, bottom); //clamp floor of neighbour to our POV

	                // If our ceiling is higher than their ceiling, render upper wall     
                    if(cropYCeiling < nbrYCeil) {   
                    	vLineTexture(renderer, textures[currentSector->texture()], x, yCeiling, nbrYCeil-1, x1, wallHeight, distanceIndex, top, bottom, alpha);
                    }       

	                // If our floor is lower than their floor, render bottom wall
                    if(cropYFloor > nbrYFloor) {
						vLineTexture(renderer, textures[currentSector->texture()], x, nbrYFloor+1, yFloor, x1, wallHeight, distanceIndex, top, bottom, alpha);
                    }
					
					//If this opening is closed with a door, render door
                    if(isDoorLocked)
                    {
                    	vLineTexture(renderer, doorTexture, x, nbrYCeil-1, nbrYFloor+1, beginx, wallHeight, distanceIndex, top, bottom, alpha);
                    }

                    // Shrink the remaining window below this ceiling and floor
	                ytop[x] = gfx_util::clamp(std::max(cropYCeiling, nbrYCeil), top, screenHeight-1);
	                ybottom[x] = gfx_util::clamp(std::min(cropYFloor, nbrYFloor), 0, bottom);          
	            }
	            else{
                    // No neighbors, render wall from top to bottom
                    vLineTexture(renderer, textures[currentSector->texture()], x, yCeiling, yFloor, x1, wallHeight, distanceIndex, top, bottom, alpha);
	            }
	        }

	       	//if(e->getSector()->getId() == currentSector->getId()) 
    		
	        //add sector-neighbours to renderQueue
	        if(neighbour != NULL && endx >= beginx && !(isDoorLocked)){
	        	sectorView nbrSectorView{neighbour, beginx, endx, minTopY, maxBotY};
	        	sectorRenderQueue.push(nbrSectorView);
	        }
		}
        	
        //Render enemies
		if(!enemies.empty()){
        	for(Enemy* e : enemies)
        		if(currentSector->getId() == e->getSector()->getId()) 
        			enemyViews.push_back({currentSectorView, e});
	    }
	    
		++renderedSectors[currentSector->getId()-1];
		///END RENDER SECTOR
	}
	
	for (enemyView ev: enemyViews)
		render_util::renderEnemy(renderer, enemyTexture, &ev.view, player, ev.enemy, screenHeight, screenWidth);

}

// vline: Draw a vertical line on screen, with a different color pixel in top & bottom 
void render_util::drawVLine(SDL_Renderer* renderer, int x1, int y1,int y2, int red, int green, int blue, int shade, int screenHeight, int screenWidth)
{
	//int H = 480; // window-height
	//int W = 640; // window-width
    y1 = gfx_util::clamp(y1, 0, screenHeight-1);
    y2 = gfx_util::clamp(y2, 0, screenHeight-1);

    // if calculated shade (color - shade) is under the threshold, set the color as the threshold
    SDL_SetRenderDrawColor(renderer, (red - shade < red / 4) ? red / 4 : red - shade, (green - shade < green / 4) ? green / 4 : green - shade, (blue - shade < blue / 4) ? blue / 4 : blue - shade, 0xFF);//vegg
    SDL_RenderDrawLine(renderer, x1, y1, x1, y2);

    //Borders?
    SDL_SetRenderDrawColor(renderer, 5, 5, 5, 0.5f);
    SDL_RenderDrawPoint(renderer, x1, y1);
    SDL_RenderDrawPoint(renderer, x1, y2);
}

void render_util::vLineTexture(SDL_Renderer* renderer, SDL_Texture* texture,int x, int y1, int y2, int beginx, float wallHeight, float widthIndex, int top, int bottom, int alpha)
{
	/* vline: Draw a vertical line on screen, with a different color pixel in top & bottom */
	int textureWidth = 256, textureHeight = 256;

	int yCeiling = gfx_util::clamp(y1, top, bottom);
	int yFloor = gfx_util::clamp(y2, top, bottom);

	// std::cout << "Index " << wallLength << std::endl;
	int textureX = (x-beginx) / widthIndex;

	//Set bounds for linerect
	SDL_Rect line;
    line.w = 1;
    line.h = yFloor-yCeiling;
	line.x = x;
	line.y = yCeiling;

	float partWh = yFloor-yCeiling;
	float part = partWh/wallHeight;
	float overFlowTop = (yCeiling-y1);
	float offset = (overFlowTop/wallHeight)*textureHeight;
	//std::cout << "yCeiling " << yCeiling << " y1 " << y1 << " X: " << x << " Oft: " << overFlowTop << " Offset: " << offset << std::endl;

	//Set crop
	SDL_Rect crop;
    crop.w = 1;
    crop.h = textureHeight*part;
	crop.x = textureX % textureWidth;
	crop.y = offset;


	SDL_SetTextureColorMod(texture, alpha, alpha, alpha);


    SDL_RenderCopy(renderer, texture, &crop, &line);
}

void render_util::renderEnemy(SDL_Renderer* renderer, SDL_Texture* texture, sectorView* sectorV, Player* player, Enemy* enemy, int screenHeight, int screenWidth) {
	float hfov = 0.73f*screenHeight; 		// Horizontal fov (Field of Vision)
	float vfov = 0.2f*screenHeight;    		// Vertical fov (Field of Vision)
	sector* currentSector = sectorV->thisSector;

	float px = player->x(), py = player->y(), pz = player->z();
	float ex = enemy->x(), ey = enemy->y(), ez = enemy->z();

	int enemySize = 1000; // enemy-scale

	// calculate distance between player and enemy
	float distance = enemySize * 1 / sqrt(pow(ex-px, 2) + pow(ey-py, 2));// + pow(ez-pz, 2));
	
	// don't render if too far away
	//if(distance < 100) return;

	float psin = player->anglesin(); float pcos = player->anglecos();
    float enemyAx = ex - px; float enemyAy = ey - py;
    float etx = enemyAx * psin - enemyAy * pcos; float etz = enemyAx * pcos + enemyAy * psin;

    // Is the enemy in front of player
	if(etz <= 0) return;

	float exscale = hfov / etz; float eyscale = vfov / etz;

	int enemyX = screenWidth / 2 - (int) (etx * exscale);
    int enemyY = screenHeight / 2 - (int) ((currentSector->floor() - pz + etz * player->yaw()) * eyscale);

    // std::cout << "EnemyX: " << enemyX << " EnemyY: " << enemyY << " Distance: " << distance << std::endl;
    // Rendering
	SDL_Rect enemySprite;

	//Set bounds for enemy
    enemySprite.w = (int) distance;
    enemySprite.h = (int) distance*2;
    enemySprite.x = enemyX - enemySprite.w/2;
	enemySprite.y = enemyY - enemySprite.h + (enemySprite.h/10);
	//std::cout << "EnemyX: " << enemySprite.x << " Width: " << enemySprite.w << " Distance: " << distance << std::endl;

	//std::cout << "Sector ID=" << currentSector->getId() << " Enemy.x=" << enemySprite.x << " cropLeft=" << sectorV->leftCropX << " cropRight=" << sectorV->rightCropX << std::endl;
	//if enemy not in render-room for sector. dont render
	// y1 = y, y2= y+enemysprite.h, 
	int x2 = enemySprite.x + enemySprite.w;
	int y2 = enemySprite.y + enemySprite.h;
	bool isIntersect = gfx_util::intersectBox(enemySprite.x, enemySprite.y, x2, y2, sectorV->leftCropX, sectorV->topCropY, sectorV->rightCropX, sectorV->botCropY);
	if(!isIntersect){
		enemy->setRender(false);
		//std::cout << " NORENDER" << std::endl;
		return;
	}
	enemy->setRender(true);
	/*
	if(!(enemySprite.x > sectorV->leftCropX && (enemySprite.x+enemySprite.w) < sectorV->rightCropX)){
		//std::cout << " NORENDER" << std::endl;
		return;
	}
	*/

	enemy->setRect(enemySprite);

	SDL_Rect crop;
    crop.w = 328;
    crop.h = 584;
	crop.x = 0;
	crop.y = 0;

	SDL_RenderCopy(renderer, texture, &crop, &enemySprite);
}

void render_util::renderSector(sector currentSect){

}

//Temporary method for showing a top-down view on screen.
void render_util::render_map(SDL_Renderer* renderer, Player* player, SDL_Texture* texture, std::vector<vertex> vertices, int screenHeight, int screenWidth){

	int vCount = vertices.size();
    
    int yOffset = 100; // displaces map by a given y //-150 
    int xOffset = screenWidth - 100;  // displaces map by a give x  //250

    // Render player on map
    SDL_Rect prect;
    prect.w = 5; prect.h = 5;
    prect.x = (xOffset) - prect.w / 2; prect.y = (yOffset) - prect.h / 2;

    SDL_SetRenderDrawColor(renderer, 0x55, 0xFF, 0x55, 0xFF); // map-color, Blue/green-ish
    SDL_RenderDrawLine(renderer, xOffset, yOffset, xOffset, yOffset); // render map 
    SDL_SetRenderDrawColor(renderer, 0xBB, 0xBB, 0xBB, 0xFF); // map-color, Blue/green-ish
    SDL_RenderFillRect(renderer, &prect); // render map 

    //get player-variables
    Vector3f posVector = player->position();
    float playerX = posVector(0); float playerY = posVector(1); float playerZ = posVector(2);
    float anglecos = player->anglecos(); float anglesin = player->anglesin();

    // Render map
    for (int i = 0; i < vCount; i++) {
        vertex a = vertices[i];
        vertex b = vertices[0];
        if (i < vCount-1)
            b = vertices[i+1];


        int range = 60;
        if(std::abs(a.x()- (std::abs(playerX))) > range || std::abs(a.y()- (std::abs(playerY))) > range ||
        	std::abs(a.x()- (std::abs(playerX))) > range || std::abs(b.y()- (std::abs(playerY))) > range)
        	continue;

        //Calculate 
        float txa = a.x()-playerX, tya = a.y()-playerY;
        float txb = b.x()-playerX, tyb = b.y()-playerY;

        float tza = txa*anglecos + tya*anglesin;
        float tzb = txb*anglecos + tyb*anglesin;
              txa = txa*anglesin - tya*anglecos;
              txb = txb*anglesin - tyb*anglecos;

        SDL_SetRenderDrawColor(renderer, 0x00, 0x77, 0xFF, 0xFF); // map-color, Blue/green-ish
        SDL_RenderDrawLine(renderer, -txa + xOffset, -tza + yOffset, -txb + xOffset, -tzb + yOffset); // render map
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF); // wall-color, Yellow
    }
}

void render_util::render_player_hp(SDL_Renderer* renderer, Player* player, int screenHeight, int screenWidth){
	int yOffset = 30; 
    int xOffset = 30; 

    // background and hp bars
    SDL_Rect background;
    background.w = (100*1.6) + 2; background.h = 18;
    background.x = xOffset-1; background.y = yOffset-1;
    SDL_SetRenderDrawColor(renderer, 0x5A, 0x5A, 0x5A, 0xFF);
    SDL_RenderFillRect(renderer, &background); // fill bar
    SDL_RenderCopy(renderer, NULL, NULL, &background);

    SDL_Rect hp_bar;
    hp_bar.w = player->hp()*1.6; hp_bar.h = 16;
    hp_bar.x = xOffset; hp_bar.y = yOffset;
    if(player->hp() > 50)
    	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF); // hp color - maybe green? 0x00FF00
    else
		SDL_SetRenderDrawColor(renderer, 0xD2, 0x05, 0x05, 0xFF); // hp color - maybe green? 0x00FF00
    SDL_RenderFillRect(renderer, &hp_bar); // fill bar
    SDL_RenderCopy(renderer, NULL, NULL, &hp_bar);
}

