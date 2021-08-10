#pragma once

// From the C++ Standard Library
#include <cstdint>
#include <functional>

// Local Includes
#include "Patient.h"

/// <summary>
/// Class representing one of many stations that perform COVID-19 vaccination at an average rate of 15 vaccincations/hour, with exponentially distributed service times.
/// </summary>
class VaccinationStation
{
public:
	/// <summary>
	/// Generate a VaccinationStation instance with default arguments.
	/// </summary>
	VaccinationStation() = default;

	/// <summary>
	/// Generate a VaccinationStation instance with a given identifier.
	/// </summary>
	/// <param name="stationId">A number to unqiuely identify this station.</param>
	VaccinationStation(int stationId);

	/// <summary>
	/// Given a patient and the current "system time" of the Vaccination Station, record the amount of time that administation 
	/// of the vaccination takes, given that the station performs an average of 15 vaccinatios/hour, exponentially distributed. 
	/// </summary>
	/// <param name="patient">A reference to the patient receiving the vaccination.</param>
	/// <param name="timeNow">The current system time, used to keep track of station availability.</param>
	void performVaccination(Patient& patient, unsigned timeNow);

	/// <summary>
	/// Reset the station to a new day, effectively clearing any ongoing vaccine administrations.
	/// </summary>
	void nextDay();

	/// <summary>
	/// Check to see if the station is available to receive another patient.
	/// </summary>
	/// <param name="currentTime">The current system time, used to compare against the most recent vaccination performed.</param>
	/// <returns>True if the station can accept a new patient, false otherwise.</returns>
	bool isAvailable(unsigned currentTime) const;

private:
	// Number of vaccinations that can be performed within one hour, on average. 
	constexpr static int AVERAGE_INJECTIONS_PER_HOUR = 15;

	// A unique identifier for the station object.
	int stationId = -1;

	// Callback to get a randomized sample time, given the average rate of vaccinations occur at exponentially distributed times.
	std::function<double()> getServiceTime;

	// How long it takes to administer the vaccine to the most recent patient.
	unsigned currentVaccinationDuration = 0;

	// The point in time when the most recent patient was accepted.
	unsigned currentVaccinationStart = 0;
};

