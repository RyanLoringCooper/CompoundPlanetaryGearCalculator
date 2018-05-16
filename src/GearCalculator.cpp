#include <iostream>
#include <thread>
#include <cmath>
#include "GearCalculator.h"

// should be in mm
#define ROUGHLY_EQUAL_THRESHOLD .1
#define TEETH_DISTANCE_THRESHOLD .6

int GearCalculator::checkGearRelation(const int &sTeeth, const int &pTeeth, const int &rTeeth) const {
	return sTeeth+(pTeeth<<1) == rTeeth;
}

bool GearCalculator::checkSunRingRelation(const int &sTeeth, const int &rTeeth, const int &numPlanets) const {
	double val = (sTeeth+rTeeth)/numPlanets;
	return val-(int)val == 0;
}

/*	double GearCalculator::getNextStageDiameteralPitch() const {
	return firstModule*(first[SUN]+first[PLANET])/(second[SUN]+second[PLANET]);
}
*/
int GearCalculator::getNumTeeth(const double &teethWidth, const double &diameter) const {
	return (int)((diameter*M_PI)/teethWidth);
}

/* returns the size of the teeth that would fit on this gear
 * @param numTeeth
 *		the number of teeth to be put on this gear
 * @param diameter
 * 		the diameter of the gear
 */
double GearCalculator::getTeethWidth(const int &numTeeth, const double &diameter) const {
	return (diameter*M_PI)/numTeeth;
}

double GearCalculator::getGearDiameter(const int &numTeeth, const double &diameteralPitch) const {
	return diameteralPitch*numTeeth;
}

bool GearCalculator::roughlyEqual(const double &one, const double &two) const {
	return abs(one-two) <= ROUGHLY_EQUAL_THRESHOLD;
}

double GearCalculator::getDiameteralPitch(const int &numTeeth, const double &diameter) const {
	return diameter/numTeeth;
}

bool GearCalculator::sunPlanetFitInRing(const double &dp, const double &ds, const double &dr) {
	return roughlyEqual(dr, dp*2+ds);
}

inline bool GearCalculator::isWholeNumber(double num) const {
	return num-(int)num == 0;
}

bool GearCalculator::planetsHaveSpace(const double &dp, const double &ds, const int &numPlanets) {
	double rp = dp/2, rs = ds/2, theta = 2*M_PI/numPlanets;
	double distBetweenPlanetCenters = 2*pow((rs+rp), 2)-2*rs*rp*cos(theta);
	double spaceBetweenTeeth = distBetweenPlanetCenters-2*rp;
	return spaceBetweenTeeth > TEETH_DISTANCE_THRESHOLD;
}

void GearCalculator::planetThread(const int &planetTeeth, const int &numPlanets, const int &ringTeeth, const double &diameteralPitch) {
	double dp = getGearDiameter(planetTeeth, diameteralPitch);
	for(int sunTeeth = minTeeth; sunTeeth <= maxSunPlanetTeeth; sunTeeth++) {
		double ds = getGearDiameter(sunTeeth, diameteralPitch); 
		if(planetsHaveSpace(dp, ds, numPlanets)) {
            double dr;
			if(sunPlanetFitInRing(dp, ds, (dr = getGearDiameter(ringTeeth, diameteralPitch))) && checkGearRelation(sunTeeth, planetTeeth, ringTeeth) && checkSunRingRelation(sunTeeth, ringTeeth, numPlanets)) {
				firstStagesMut.lock();
				firstStages.emplace_back(sunTeeth, planetTeeth, ringTeeth, numPlanets, ds, dp, dr, diameteralPitch);
				firstStagesMut.unlock();
			}
		}
	}
}

void GearCalculator::numPlanetsThread(const int &numPlanets,const double &minTeethSize, const double &diameter) {
	int ringTeeth = getNumTeeth(minTeethSize, diameter);
	double toothSize = getTeethWidth(ringTeeth, diameter);
	double diameteralPitch = getDiameteralPitch(ringTeeth, diameter);
	int teethRange = maxSunPlanetTeeth-minTeeth+1;
	std::thread threads[teethRange];
	for(int planetTeeth = minTeeth; planetTeeth <= maxSunPlanetTeeth; planetTeeth++) {
		threads[planetTeeth-minTeeth] = std::thread(&GearCalculator::planetThread, this, planetTeeth, numPlanets, ringTeeth, diameteralPitch) ;
	}
	for(int i = 0; i < teethRange; i++) {
		threads[i].join();
	}
}

void GearCalculator::diameterThread(const double &minTeethSize, const double &diameter) {
	int planetRange = maxPlanets-minPlanets+1;
	std::thread threads[planetRange];
	for(int numPlanets = minPlanets; numPlanets <= maxPlanets; numPlanets++) {
			threads[numPlanets-minPlanets] = std::thread(&GearCalculator::numPlanetsThread, this, numPlanets, minTeethSize, diameter);
	}
	for(int i = 0; i < planetRange; i++) {
		threads[i].join();
	}
}

void GearCalculator::getFirstStages() {
    int diameterRange = ceil((maxDiameter-minDiameter)/diameterInterval);
    int threadIndex = 0;
    std::thread threads[diameterRange];
    for(double diameter = minDiameter; diameter <= maxDiameter; diameter += diameterInterval) {
        threads[threadIndex++] = std::thread(&GearCalculator::diameterThread, this, minTeethSize, diameter);
    }
    for(int i = 0; i < diameterRange; i++) {
        threads[i].join();
    }
}

void GearCalculator::findValids(const GearSet &firstStage) {
	double m2, ds, dp;
	int s1, p1, r2;
	s1 = firstStage.sunTeeth;
	p1 = firstStage.planetTeeth;
	ds = firstStage.sunDiameter;
	dp = firstStage.planetDiameter;
	for(int s2 = minTeeth; s2 <= maxSunPlanetTeeth; s2++) {
		for(int p2 = minTeeth; p2 <= maxSunPlanetTeeth; p2++) {
			m2 = firstStage.diameteralPitch*(s1+p1)/(double)(s2+p2);
			r2 = (s2+(p2<<1));
			if(m2*s2 == ds && m2*p2 == dp && isWholeNumber((s2/(r2*firstStage.numPlanets)))) {
				GearSet secondStage(s2, p2, r2, firstStage.numPlanets, ds, dp, getGearDiameter(r2, m2), m2);
				validsMut.lock();
				valids.emplace_back(firstStage, secondStage);
				validsMut.unlock();
			}
		}
	}
}

GearCalculator::GearCalculator(const int &maxSunPlanetTeeth, const int &minTeeth, const int &minPlanets, const int &maxPlanets, const double &minTeethSize, const double &minDiameter, const double &maxDiameter, const double &diameterInterval) {
	this->maxSunPlanetTeeth = maxSunPlanetTeeth;
	this->minTeeth = minTeeth;
	this->minPlanets = minPlanets;
	this->maxPlanets = maxPlanets;
	this->minTeethSize = minTeethSize;
	this->minDiameter = minDiameter;
	this->maxDiameter = maxDiameter;
    this->diameterInterval = diameterInterval;
}

void GearCalculator::run() {
	getFirstStages();
	std::thread threads[firstStages.size()];
	for(int firstStage = 0; firstStage < firstStages.size(); firstStage++) {
		threads[firstStage] = std::thread(&GearCalculator::findValids, this, firstStages[firstStage]);
	}
	for(int i = 0; i < firstStages.size(); i++) {
		threads[i].join();
	}
}

void GearCalculator::printResults(std::ostream &os) {
	os << std::string("Number of valid sets = ") << valids.size() << std::endl;
	for(int i = 0; i < valids.size(); i++) {
		os << valids[i] << std::endl;
	}
}
