#include "normal_sector_factory.hpp"
#include "vertex.hpp"

sector* NormalSectorFactory::createSector(int id, float floor_height, float ceiling_height, std::vector<vertex> v) 
{
	 return new sector{id, floor_height, ceiling_height, v};
}