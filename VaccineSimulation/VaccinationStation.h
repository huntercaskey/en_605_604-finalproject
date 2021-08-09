#pragma once

#include <cstdint>
#include <functional>
#include <random>

#include "Patient.h"

class VaccinationStation
{
public:
	VaccinationStation() = default;
	VaccinationStation(int stationId);
	void performVaccination(PatientRecord& patient, unsigned timeNow);
	void nextDay();
	bool isAvailable(unsigned currentTime) const;
private:
	constexpr static int AVERAGE_INJECTIONS_PER_HOUR = 15;
	int stationId = -1;
	std::function<double()> getServiceTime;
	unsigned currentVaccinationDuration = 0;
	unsigned currentVaccinationStart = 0;
};

