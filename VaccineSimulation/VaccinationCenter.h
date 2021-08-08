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

	void acceptPatient(NonSeniorPatient& patient);
	void acceptPatient(SeniorPatient& patient);
	void servicePendingPatients();
	void nextDay();
private:

	void processPatient(PatientRecord& patient, std::function<void(void)>& queuePatientCallback);

	// Centralized location to store all information about patients serviced
	std::list<std::reference_wrapper<PatientRecord>> patientRecords;

	// Queues to hold patients after they have checked-in, while they are waiting for an available VaccinationStation
	std::list<std::reference_wrapper<SeniorPatient>> seniorQueue;
	std::list<std::reference_wrapper<NonSeniorPatient>> nonSeniorQueue;

	// Used to handle the verification process of a patient.
	CheckInArea checkinArea;

	// Time tracking for the Vaccination Center
	constexpr static int START_TIME_MINUTES = 0;
	constexpr static int END_TIME_MINUTES = 12 * 60;
	unsigned elapsedTime = 0;
	unsigned date = 0;
	
	constexpr static int AVERAGE_ARRIVALS_PER_HOUR = 30;
	std::function<double()> getArrivalTime;

	
	static const size_t NUM_VACCINATION_STATIONS = 3;
	std::array<VaccinationStation, NUM_VACCINATION_STATIONS> vaccinationStations;
	VaccinationStation& getNextAvailableStation();
};

