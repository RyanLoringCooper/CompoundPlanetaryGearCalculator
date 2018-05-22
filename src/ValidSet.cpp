#include <iostream>
#include "ValidSet.h"

ValidSet::ValidSet(const GearSet &first, const GearSet &second) {
	this->first = first;
	this->second = second;
	this->finalRatio = getFinalRatio(first, second);
}

double ValidSet::getFinalRatio(const GearSet &first, const GearSet &second) {
   	return (1+(first.ringTeeth/((double)first.sunTeeth)))/(1-(second.planetTeeth*first.ringTeeth)/((double)second.ringTeeth*first.planetTeeth));
}
	
std::ostream &operator<<(std::ostream &os, const ValidSet &gs) {
	os 	<< "Ratio = " << gs.finalRatio << std::endl 
		<< "First:\n" << gs.first << "Second:\n" << gs.second << std::endl;
	return os;
}
