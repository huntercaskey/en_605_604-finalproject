#pragma once

#include <list>
#include <functional>
#include <random>
#include <tuple>

#include "Patient.h"

class CheckInArea
{
public:
	CheckInArea();
	void checkInPatient(PatientRecord& patient);
private:
	static constexpr uint8_t MIN_WAIT_TIME_MINUTES = 1;
	static constexpr uint8_t MAX_WAIT_TIME_MINUTES = 4;

	std::function<int()> getWaitTime;
	std::list<std::reference_wrapper<PatientRecord>> queue;

};

