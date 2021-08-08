#pragma once

#include <cstdint>
#include <functional>
#include <random>

#include "Patient.h"

class VaccinationStation
{
public:
	VaccinationStation();
	void performVaccination(PatientRecord& patient);
	void nextDay();
	unsigned getNextAvailableTime(unsigned elapsedTime) const;
private:
	constexpr static int AVERAGE_INJECTIONS_PER_HOUR = 15;
	std::function<double()> getServiceTime;
	unsigned lastServiceTime = 0;
};

