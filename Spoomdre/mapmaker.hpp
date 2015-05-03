#ifndef CLASS_MAPMAKER_H
#define CLASS_MAPMAKER_H

#include <stdio.h>
#include "sector.hpp"
#include "vertex.hpp"
#include "door.hpp"
#include "level_portal.hpp"

class mapmaker{
public:
	static std::vector<sector*> createMap();
	static std::vector<sector*> createTestMap();
	static std::vector<sector*> createShowcaseMap();
};


#endif