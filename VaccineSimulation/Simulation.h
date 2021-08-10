#pragma once

// Local Includes
#include "VaccinationCenter.h"

/// <summary>
/// Class that drives the execution of a time-based simulation of a vaccination distribution center.
/// </summary>
class Simulation
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	Simulation();

	/// <summary>
	/// Perform a simulation of the operation of a vaccination center for the provided number of days. 
	/// </summary>
	/// <param name="daysToSimulate">The number of days to run the simulation for.</param>
	void runSimulation(unsigned daysToSimulate);
private:
	/// <summary>
	/// Helper function to step through the simulation, one day at a time.
	/// </summary>
	void simulateOneDay();

	VaccinationCenter vaccinationCenter;
};
