#ifndef CLASS_ABSTRACTSECTORFACTORY_H
#define CLASS_ABSTRACTSECTORFACTORY_H

#include "sector.hpp"
#include "vertex.hpp"
#include <vector>

class AbstractSectorFactory {

 	public: 
		virtual sector* createSector(int id, float floor_height, float ceiling_height, std::vector<vertex> v, int texture) = 0;
};

#endif