#include "ValidSet.h"

ValidSet::ValidSet(const GearSet &first, const GearSet &second) {
	this->first = first;
	this->second = second;
	this->finalRatio = getFinalRatio();
}

inline double ValidSet::getFinalRatio() const {
	return 1.0/((second.ringTeeth-second.planetTeeth*first.ringTeeth/first.planetTeeth)*(first.sunTeeth/(first.ringTeeth+first.sunTeeth)));
}
	
std::ostream &operator<<(std::ostream &os, const ValidSet &gs) {
	os 	<< "Ratio = " << gs.finalRatio << std::endl 
		<< "First:\n" << gs.first << "Second:\n" << gs.second << std::endl;
	return os;
}