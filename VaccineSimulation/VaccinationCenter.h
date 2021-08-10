#pragma once

// From the C++ Standard Library
#include <array>
#include <list>
#include <vector>

// Local Includes
#include "Patient.h"
#include "VaccinationStation.h"

/// <summary>
/// Class to represent the operations of a vaccine distribution center.
/// </summary>
class VaccinationCenter
{
public:
	/// <summary>
	/// Default constructor.
	/// </summary>
	VaccinationCenter();

	/// <summary>
	/// Receive a non-senior patient into the vaccination center. This function will not affect system operation
	/// if the internal system clock has past the 12-hour mark.
	/// </summary>
	/// <param name="patientId">A unique identifier for the patient being admitted to the vaccine center.</param>
	void acceptNonSenior(int patientId);

	/// <summary>
	/// Receive a senior citizen patient into the vaccination center. This function will not affect system operation
	/// if the internal system clock has past the 12-hour mark.
	/// </summary>
	/// <param name="patientId">A unique identifier for the patient being admitted to the vaccine center.</param>
	void acceptSenior(int patientId);

	/// <summary>
	/// Perform all vaccination center operations for a 1-hour time step. 
	/// </summary>
	void stepOneHour();

	/// <summary>
	/// Reset the day-by-day state of the vaccine center.
	/// </summary>
	void nextDay();

	/// <summary>
	///  Output a human-readable report of the system's performance to stdout.
	/// </summary>
	void printReport();
private:

	// Centralized location to store all information about patients admitted to the vaccination center.
	std::vector<Patient> patientRecords;
	
	// Queues to hold patients after they have checked-in and while they are waiting for an available vaccination station.
	std::list<size_t> seniorQueue;
	std::list<size_t> nonSeniorQueue;
	std::list<size_t> newPatients;

	// Time-based variables and constants for keeping track of the overal 'system clock'.
	constexpr static int START_TIME_MINUTES = 0;
	constexpr static int END_TIME_MINUTES = 12 * 60;
	unsigned elapsedTime = 0;
	unsigned date = 0;
	
	// Constants and callbacks related to generating randomized samples of the point in time each patient arrives at the vaccination center.
	constexpr static int AVERAGE_ARRIVALS_PER_HOUR = 30;
	std::function<double()> getArrivalTime;

	// Constants and callbacks related to generating randomized samples of the length of time it takes each patient to be checked-in to the vaccination center.
	static constexpr uint8_t MIN_WAIT_TIME_MINUTES = 1;
	static constexpr uint8_t MAX_WAIT_TIME_MINUTES = 4;
	std::function<int()> getWaitTime;
	
	// Data and functions relating to the usage of stations used to vaccinate individual patients.
	static const size_t NUM_VACCINATION_STATIONS = 3;
	std::array<VaccinationStation, NUM_VACCINATION_STATIONS> vaccinationStations;
	VaccinationStation* getNextAvailableStation();
};

