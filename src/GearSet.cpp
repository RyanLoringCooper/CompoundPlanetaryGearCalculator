#include "GearSet.h"

GearSet::GearSet() {}

GearSet::GearSet(const int &sunTeeth, const int &planetTeeth, const int &ringTeeth, const int &numPlanets, const double &sunDiameter, const double &planetDiameter, const double &ringDiameter, const double &diameteralPitch) {
	this->sunTeeth = sunTeeth;
	this->planetTeeth = planetTeeth;
	this->ringTeeth = ringTeeth;
	this->numPlanets = numPlanets;
	this->sunDiameter = sunDiameter;
	this->planetDiameter = planetDiameter;
	this->ringDiameter = ringDiameter;
	this->diameteralPitch = diameteralPitch;
}

std::ostream &operator<<(std::ostream &os, const GearSet &gs) {
	os 	<< "\tSun Diameter = \t\t" << gs.sunDiameter << std::endl
		<< "\tPlanet Diameter = \t\t" << gs.planetDiameter << std::endl
		<< "\tRing Diameter = \t\t" << gs.ringDiameter << std::endl
		<< "\tSun Teeth = \t\t\t" << gs.sunTeeth << std::endl
		<< "\tPlanet Teeth = \t\t" << gs.planetTeeth << std::endl
		<< "\tRing Teeth = \t\t" << gs.ringTeeth << std::endl
		<< "\tModule = \t\t\t" << gs.diameteralPitch << std::endl;
	return os;
}
