#ifndef VALIDSET_H
#define VALIDSET_H

#include "GearSet.h"

struct ValidSet {
	GearSet first, second;
	double finalRatio;

	ValidSet(const GearSet &first, const GearSet &second); 

	inline double getFinalRatio() const; 

	friend ostream &operator<<(ostream &os, const ValidSet &gs);	
};

#endif