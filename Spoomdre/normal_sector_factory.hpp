#ifndef CLASS_NORMALSECTORFACTORY_H
#define CLASS_NORMALSECTORACTORY_H

#include "abstract_sector_factory.hpp"
#include "sector.hpp"

class NormalSectorFactory : public AbstractSectorFactory {


public: 
	sector* createSector(int id, float floor_height, float ceiling_height) override;
};

#endif