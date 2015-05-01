#ifndef CLASS_LEVELPORTAL_H
#define CLASS_LEVELPORTAL_H

//External Dependencies

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

// A portal between two levels, used for switching from one level to the next
class LevelPortal{
	//int sector_;
	float x_, y_;

	int source_map;
	int destination_map;

public:
	LevelPortal(float x, float y, int src, int dest) { x_ = x; y_ = y; source_map = src; destination_map = dest; };

	int getX() { return x_; };
	int getY() { return y_; };
	//int getSector() { return sector_; };
	int getSource() { return source_map; };
	int getDestination() { return destination_map; };
};


#endif