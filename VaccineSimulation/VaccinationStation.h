#pragma once

// From the C++ Standard Library
#include <cstdint>
#include <functional>

// Local Includes
#include "Patient.h"

class VaccinationStation
{
public:
	VaccinationStation() = default;
	VaccinationStation(int stationId);
	void performVaccination(Patient& patient, unsigned timeNow);
	void nextDay();
	bool isAvailable(unsigned currentTime) const;
private:
	constexpr static int AVERAGE_INJECTIONS_PER_HOUR = 15;
	int stationId = -1;
	std::function<double()> getServiceTime;
	unsigned currentVaccinationDuration = 0;
	unsigned currentVaccinationStart = 0;
};

