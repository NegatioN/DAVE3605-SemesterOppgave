#ifndef CLASS_LINEDEF_H
#define CLASS_LINEDEF_H

#include "vertex.hpp"


//a linedef is the line between two vertexes on the map.
//ex a line from coords y=2, x=2 to y=10, x=2
class Linedef{
Vertex left_;
Vertex right_;

public:
	Linedef(Vertex left, Vertex right);


};

#endif