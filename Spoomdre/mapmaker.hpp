#ifndef CLASS_MAPMAKER_H
#define CLASS_MAPMAKER_H

#include <stdio.h>
#include "sector.hpp"
#include "vertex.hpp"

class mapmaker{
public:
	static std::vector<sector*> createMap();
	static std::vector<sector*> createTestMap();
};


#endif