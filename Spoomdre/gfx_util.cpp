#include "gfx_util.hpp"
#include <stdio.h>
#include <Eigen/Core>

float min(float value_a, float value_b){
	float value = (value_a < value_b) ? value_a : value_b;
	return value;
}

float max(float value_a, float value_b){
	float value = (value_a > value_b) ? value_a : value_b;
	return value;
}

//if input is higher than max or lower than min, return closest option
float clamp(float input, float min, float max){
	if(input < min)
		return min;
	else if(input > max)
		return max;

	return input;
}

float vcp(float x0, float y0, float x1, float y1)
{
	return ((x0 * y1) - (x1 * y0));
}

//does the two boxes intersect?
bool intersectBox(float x0, float y0, float x1, float y1,
	float x2, float y2, float x3, float y3){
	return overlap(x0,y0,x1,y1) && overlap(x2,y2,x3,y3);
}

//find out if number-ranges overlap. Used to determine intersects
bool overlap(float a0, float b0, float a1, float b1){
	return std::min(a0,a1) <= std::max(b0,b1) && std::min(b0,b1) <= std::max(a0,a1);
}

float pointSide(float px, float py,float x0, float y0, float x1, float y1){
	return vcp((x1-x0), (y1-y0), (px-x0), (py-y0));
}

xy intersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4){
	xy pos;
	pos.x = vcp( vcp( x1,y1,x2,y2 ), ( x1 - x2 ), vcp(x3,y3,x4,y4) , ( ( x3 - x4 ) / vcp( ( x1-x2 ),( y1-y2 ),( x3-x4 ),( y3-y4 ) ) ));
	pos.y = vcp( vcp( x1,y1,x2,y2 ), ( y1 - y2 ), vcp(x3,y3,x4,y4) , ( ( y3 - y4 ) / vcp( ( x1-x2 ),( y1-y2 ),( x3-x4 ),( y3-y4 ) ) ));
	return pos;
}