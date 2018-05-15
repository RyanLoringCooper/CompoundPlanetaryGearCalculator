#ifndef GEARSET_H
#define GEARSET_H

#include <iostream>

struct GearSet {
	int sunTeeth, planetTeeth, ringTeeth, numPlanets;
	double sunDiameter, planetDiameter, ringDiameter;
	double diameteralPitch;

	GearSet();
	GearSet(const int &sunTeeth, const int &planetTeeth, const int &ringTeeth, const int &numPlanets, const double &sunDiameter, const double &planetDiameter, const double &ringDiameter, const double &diameteralPitch);
	
	friend ostream &operator<<(ostream &os, const GearSet &gs);	
};

#endif