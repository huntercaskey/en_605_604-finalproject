#pragma once

// Local Includes
#include "VaccinationCenter.h"

class Simulation
{
public:
	Simulation();
	void runSimulation(unsigned daysToSimulate);
private:
	void simulateOneDay();
	VaccinationCenter vaccinationCenter;
};
