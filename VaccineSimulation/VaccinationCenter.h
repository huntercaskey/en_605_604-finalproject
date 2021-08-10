#pragma once

#include <array>
#include <list>

#include "Patient.h"
#include "CheckInArea.h"
#include "VaccinationStation.h"

class VaccinationCenter
{
public:
	VaccinationCenter();
	void acceptNonSenior(int patientId);
	void acceptSenior(int patientId);
	void stepOneHour();
	void nextDay();
	void printReport();
private:

	// Centralized location to store all information about patients serviced
	std::vector<PatientRecord> patientRecords;
	
	std::list<size_t> newPatients;

	// Queues to hold patients after they have checked-in, while they are waiting for an available VaccinationStation
	std::list<size_t> seniorQueue;
	std::list<size_t> nonSeniorQueue;

	// Used to handle the verification process of a patient.
	CheckInArea checkinArea;

	// Time tracking for the Vaccination Center
	constexpr static int START_TIME_MINUTES = 0;
	constexpr static int END_TIME_MINUTES = 12 * 60;
	unsigned elapsedTime = 0;
	unsigned date = 0;
	
	static constexpr uint8_t MIN_WAIT_TIME_MINUTES = 1;
	static constexpr uint8_t MAX_WAIT_TIME_MINUTES = 4;
	std::function<int()> getWaitTime;

	constexpr static int AVERAGE_ARRIVALS_PER_HOUR = 30;
	std::function<double()> getArrivalTime;

	
	static const size_t NUM_VACCINATION_STATIONS = 3;
	std::array<VaccinationStation, NUM_VACCINATION_STATIONS> vaccinationStations;
	VaccinationStation* getNextAvailableStation();
};

