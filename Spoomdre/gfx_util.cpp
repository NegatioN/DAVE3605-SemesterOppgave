#include "gfx_util.hpp"
#include <stdio.h>
#include <Eigen/Core>

//if input is higher than max or lower than min, return closest option
float clamp(float input, float min, float max){
	if(input < min)
		return min;
	else if(input > max)
		return max;

	return input;
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