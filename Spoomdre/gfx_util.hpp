#ifndef GFX_UTIL_H
#define GFX_UTIL_H

//last ned eigen3 for matte. vectorer etc.    libeigen3-dev
// ex: Eigen::Vector3f (tror jeg)

struct xy{float x,y;}; // struct used for returning a pos

class gfx_util {
	public:
	static float clamp(float input, float min, float max); //limits the input to be within min-max
	static float vcp(float x0, float y0, float x1, float y1);//Vector cross product
	static bool overlap(float a0, float b0, float a1, float b1); //determine if number-ranges overlap.
	static bool intersectBox(float x0, float y0, float x1, float y1, 
		float x2, float y2, float x3, float y3); //finds if the two boxes(defined by two points each), 
												//intersect or not.
	static float pointSide(float px, float py,
				float x0, float y0, float x1, float y1);//Determine which side of a line the point
														// is on, return value is >0, =0 or <0
	static xy intersect(float x1, float y1, float x2, float y2, 
				float x3, float y3, float x4, float y4);//Calculate the point of intercetion
														// between two lines
};

#endif