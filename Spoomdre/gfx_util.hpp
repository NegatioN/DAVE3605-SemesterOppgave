#ifndef CLASS_GFX_UTIL_H
#define CLASS_GFX_UTIL_H

//last ned eigen3 for matte. vectorer etc.    libeigen3-dev
// ex: Eigen::Vector3f (tror jeg)

struct xy{float x,y;}; // struct used for returning a pos

float min(float value_a, float value_b);//return smaller of two floats -should use template in future
float max(float value_a, float value_b);//return greater of two floats -should use template in future
float clamp(float input, float min, float max); //limits the input to be within min-max
float vcp(float x0, float y0, float x1, float y1);//Vector cross product
bool overlap(float a0, float b0, float a1, float b1); //determine if number-ranges overlap.
bool intersectBox(float x0, float y0, float x1, float y1, 
	float x2, float y2, float x3, float y3); //finds if the two boxes(defined by two points each), 
											//intersect or not.
float pointSide(float px, float py,
			float x0, float y0, float x1, float y1);//Determine which side of a line the point
													// is on, return value is >0, =0 or <0
xy intersect(float x1, float y1, float x2, float y2, 
			float x3, float y3, float x4, float y4);//Calculate the point of intercetion
													// between two lines

#endif