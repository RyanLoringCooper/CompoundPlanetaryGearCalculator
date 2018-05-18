#include <iostream>
#include "ValidSet.h"

ValidSet::ValidSet(const GearSet &first, const GearSet &second) {
	this->first = first;
	this->second = second;
	this->finalRatio = getFinalRatio();
}

inline double ValidSet::getFinalRatio() const {
    double rhs = (second.planetTeeth*(double)first.ringTeeth)/first.planetTeeth;
    double toppest = second.ringTeeth-rhs;
    std::cout << toppest << " - " << rhs << std::endl;
	double bottom = (toppest*(first.sunTeeth/(double)(first.ringTeeth+first.sunTeeth)));
    return bottom;
}
	
std::ostream &operator<<(std::ostream &os, const ValidSet &gs) {
	os 	<< "Ratio = " << gs.finalRatio << std::endl 
		<< "First:\n" << gs.first << "Second:\n" << gs.second << std::endl;
	return os;
}
