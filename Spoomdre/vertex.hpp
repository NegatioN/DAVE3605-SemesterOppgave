#ifndef CLASS_VERTEX_H
#define CLASS_VERTEX_H

//vertex is merely a point on our map
class vertex{
int x_;
int y_;
public:
	vertex(int x, int y) : x_{x}, y_{y}{};
	int x(){ return x_; };
	int y(){ return y_; };
};

#endif