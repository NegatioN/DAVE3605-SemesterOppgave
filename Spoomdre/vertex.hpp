#ifndef CLASS_VERTEX_H
#define CLASS_VERTEX_H

//vertex is merely a point on our map
class vertex{
float x_;
float y_;
public:
	vertex(float x, float y) : x_{x}, y_{y}{};
	float x(){ return x_; };
	float y(){ return y_; };
};

#endif