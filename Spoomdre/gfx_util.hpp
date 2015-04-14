#ifndef CLASS_GFX_UTIL_H
#define CLASS_GFX_UTIL_H

//last ned eigen3 for matte. vectorer etc.    libeigen3-dev
// ex: Eigen::Vector3f (tror jeg)

float clamp(float input, float min, float max); //limits the input to be within min-max
bool overlap(float a0, float b0, float a1, float b1); //determine if number-ranges overlap.
//finds if the two boxes(defined by two points each), intersect or not.
bool intersectBox(float x0, float y0, float x1, float y1,
	float x2, float y2, float x3, float y3); 


#endif