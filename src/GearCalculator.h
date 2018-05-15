#ifndef GEARCALCULATOR_H
#define GEARCALCULATOR_H

#include <mutex>
#include <vector>
#include "ValidSet.h"
#include "GearSet.h"

class GearCalculator {
//	int maxRingTeeth;
//	double maxPlanetToSunRatio;
	int maxSunPlanetTeeth, minTeeth;
	int minPlanets, maxPlanets;
	double outerDiameter, minTeethSize;
	std::mutex validsMut, firstStagesMut;
	std::vector<ValidSet> valids;
	std::vector<GearSet> firstStages;

	int checkGearRelation(const int &sTeeth, const int &pTeeth, const int &rTeeth) const;
	bool checkSunRingRelation(const int &sTeeth, const int &rTeeth, const int &numPlanets) const; 
	bool sunPlanetFitInRing(const double &dp, const double &ds, const double &dr); 
    bool planetsHaveSpace(const double &dp, const double &ds, const int &numPlanets);

//	double getNextStageDiameteralPitch() const;

	/* returns the size of the teeth that would fit on this gear
	 * @param numTeeth
	 *		the number of teeth to be put on this gear
	 * @param diameter
	 * 		the diameter of the gear
	 */
	double getTeethWidth(const int &numTeeth, const double &diameter) const;
	int getNumTeeth(const double &teethWidth, const double &diameter) const;
	double getGearDiameter(const int &numTeeth, const double &diameteralPitch) const; 
	double getDiameteralPitch(const int &numTeeth, const double &diameter) const;


	bool roughlyEqual(const double &one, const double &two) const;
	inline bool isWholeNumber(double num) const;

	void planetThread(const int &planetTeeth, const int &numPlanets, const int &ringTeeth, const double &diameteralPitch); 
	void numPlanetsThread(const int &numPlanets,const double &minTeethSize, const double &diameter);

	void getFirstStages(const double &minTeethSize, const double &diameter); 
	void findValids(const GearSet &firstStage);
public:
	GearCalculator(const int &maxSunPlanetTeeth, const int &minTeeth, const int &minPlanets, const int &maxPlanets, const double &minTeethSize, const double &outerDiameter);
	void run(); 
	void printResults(const std::ostream &os);
};

#endif