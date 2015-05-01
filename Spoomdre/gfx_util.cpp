#include "gfx_util.hpp"
#include <iostream>

//if input is higher than max or lower than min, return closest option
float gfx_util::clamp(float input, float min, float max){
	return std::min(std::max(input, min), max);
}

float gfx_util::vcp(float x0, float y0, float x1, float y1)
{
	return ((x0 * y1) - (x1 * y0));
}

//does the two boxes intersect?
bool gfx_util::intersectBox(float x0, float y0, float x1, float y1,
	float x2, float y2, float x3, float y3){
	return overlap(x0,x1,x2,x3) && overlap(y0,y1,y2,y3);
}

//find out if number-ranges overlap. Used to determine intersects
bool gfx_util::overlap(float a0, float a1, float b0, float b1){
	return std::min(a0,a1) <= std::max(b0,b1) && std::min(b0,b1) <= std::max(a0,a1);
}

float gfx_util::pointSide(float px, float py,float x0, float y0, float x1, float y1){
	return vcp((x1-x0), (y1-y0), (px-x0), (py-y0));
}

xy gfx_util::intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	xy pos;
	// Eigen::Vector2f line1(x2-x1,y2-y1);
	// Eigen::Vector2f line2(x4-x3,y4-y3);
	pos.x = vcp( vcp( x1,y1,x2,y2 ), ( x1 - x2 ), vcp(x3,y3,x4,y4) ,  ( x3 - x4 )) / vcp( ( x1-x2 ),( y1-y2 ),( x3-x4 ),( y3-y4 ) );
	pos.y = vcp( vcp( x1,y1,x2,y2 ), ( y1 - y2 ), vcp(x3,y3,x4,y4) ,  ( y3 - y4 )) / vcp( ( x1-x2 ),( y1-y2 ),( x3-x4 ),( y3-y4 ) );
	return pos;
}
bool gfx_util::hitScan(Vector3f position, Vector3f enemyPos, SDL_Rect hitBox, Vector3f direction){
	
	direction *= 100; //shot travels 100 in direction player is looking
	direction += position; //add current position to this.


	float halfWidth = hitBox.w/2;
	float mobX1 = enemyPos(0)-halfWidth;
	float mobX2 = enemyPos(0)+halfWidth;


	std::cout << "CheckValues X1=" << mobX1 << " X2=" << mobX2 << std::endl;
	std::cout << "Mob X=" << enemyPos(0) << " Y=" << enemyPos(1) << " halfWidth=" << halfWidth << std::endl; 

	//get intersection-point of line from player-->shot and enemyLeft-->enemyRight
	xy pos = gfx_util::intersect(position(0), position(1),  direction(0),  direction(1), 
	 	mobX1,  enemyPos(1),  mobX2, enemyPos(1));
	
	//are these intersection-points within the bounds of the specified second line?
	// ex x3,y3 <--this space--> x4, y4. if yes, it's a hit.
	if(pos.x <= mobX2 && pos.x >= mobX1){
		if(pos.y <= enemyPos(1) && pos.y >= enemyPos(1))
			return true;
		else if(pos.y <= enemyPos(1) && pos.y >= enemyPos(1))
			return true;
	}
	else if(pos.x <= mobX2 && pos.x >= mobX1){
		if(pos.y <= enemyPos(1) && pos.y >= enemyPos(1))
			return true;
		else if(pos.y <= enemyPos(1) && pos.y >= enemyPos(1))
			return true;
	}

	return false;
}

