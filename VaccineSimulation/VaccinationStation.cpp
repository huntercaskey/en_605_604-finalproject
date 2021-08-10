// Class Header Include
#include "VaccinationStation.h"

// From the C++ Standard Library
#include <random>

// Local Includes
#include "Patient.h"

VaccinationStation::VaccinationStation(int stationId) : stationId(stationId)
{
    std::default_random_engine generator;
    std::exponential_distribution<> distribution(AVERAGE_INJECTIONS_PER_HOUR);
    this->getServiceTime = std::bind(distribution, generator);
}

void VaccinationStation::performVaccination(Patient& patient, unsigned timeNow)
{
    this->currentVaccinationStart = timeNow;
    double distributionSample = this->getServiceTime();
    
    // Scale to a factor of minutes within the hour, and add 1 to shift the distribution such that 1 minute is the minimum service time.
    int normalizationFactor = 60; 
    int waitTime = int(normalizationFactor * distributionSample) + 1;
    this->currentVaccinationDuration = waitTime;
    patient.setVaccinationStationServiceTime(waitTime);
}

void VaccinationStation::nextDay()
{
    currentVaccinationDuration = 0;
}

bool VaccinationStation::isAvailable(unsigned currentTime) const
{
    unsigned nextAvailableFreeTime = this->currentVaccinationStart + this->currentVaccinationDuration;

    if (currentTime >= nextAvailableFreeTime)
    {
        return true;
    }

    return false;
}
