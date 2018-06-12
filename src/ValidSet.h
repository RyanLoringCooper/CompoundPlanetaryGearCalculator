#ifndef VALIDSET_H
#define VALIDSET_H

#include "GearSet.h"

struct ValidSet {
	GearSet first, second;
	double finalRatio;

	ValidSet(const GearSet &first, const GearSet &second); 

	static double getFinalRatio(const GearSet &first, const GearSet &second); 

	friend std::ostream &operator<<(std::ostream &os, const ValidSet &gs);	
};

#endif
