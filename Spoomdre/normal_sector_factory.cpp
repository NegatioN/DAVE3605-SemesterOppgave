#include "normal_sector_factory.hpp"

sector* NormalSectorFactory::createSector(int id, float floor_height, float ceiling_height) 
{
	static sector s{id, floor_height, ceiling_height};
	return &s;
}