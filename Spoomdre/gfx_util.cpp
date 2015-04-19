#include "gfx_util.hpp"
#include <stdio.h>
#include <Eigen/Core>

float gfx_util::min(float value_a, float value_b){
	float value = (value_a < value_b) ? value_a : value_b;
	return value;
}

float gfx_util::max(float value_a, float value_b){
	float value = (value_a > value_b) ? value_a : value_b;
	return value;
}

//if input is higher than max or lower than min, return closest option
float gfx_util::clamp(float input, float min, float max){
	if(input < min)
		return min;
	else if(input > max)
		return max;

	return input;
}

float gfx_util::vcp(float x0, float y0, float x1, float y1)
{
	return ((x0 * y1) - (x1 * y0));
}

//does the two boxes intersect?
bool gfx_util::intersectBox(float x0, float y0, float x1, float y1,
	float x2, float y2, float x3, float y3){
	return overlap(x0,y0,x1,y1) && overlap(x2,y2,x3,y3);
}

//find out if number-ranges overlap. Used to determine intersects
bool gfx_util::overlap(float a0, float b0, float a1, float b1){
	return std::min(a0,a1) <= std::max(b0,b1) && std::min(b0,b1) <= std::max(a0,a1);
}

float gfx_util::pointSide(float px, float py,float x0, float y0, float x1, float y1){
	return vcp((x1-x0), (y1-y0), (px-x0), (py-y0));
}

xy gfx_util::intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	xy pos;
	pos.x = vcp( vcp( x1,y1,x2,y2 ), ( x1 - x2 ), vcp(x3,y3,x4,y4) , ( ( x3 - x4 ) / vcp( ( x1-x2 ),( y1-y2 ),( x3-x4 ),( y3-y4 ) ) ));
	pos.y = vcp( vcp( x1,y1,x2,y2 ), ( y1 - y2 ), vcp(x3,y3,x4,y4) , ( ( y3 - y4 ) / vcp( ( x1-x2 ),( y1-y2 ),( x3-x4 ),( y3-y4 ) ) ));
	return pos;
}