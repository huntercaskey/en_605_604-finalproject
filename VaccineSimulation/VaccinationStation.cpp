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
    // Update the last vaccine service time, for use within isAvailable()
    this->currentVaccinationStart = timeNow;

    // Generate the sample time and scale to a factor of minutes within the hour, adding 1 to shift the distribution such that 1 minute is the minimum service time.
    double distributionSample = this->getServiceTime();
    int normalizationFactor = 60; 
    int waitTime = int(normalizationFactor * distributionSample) + 1;

    // Update the internal time it takes to administer the vaccine as well as the patient's record.
    this->currentVaccinationDuration = waitTime;
    patient.setVaccinationStationServiceTime(waitTime);
}

void VaccinationStation::nextDay()
{
    // Reset the interal logic for tracking the last administered vaccine, essentially makes isAvailable() work 
    // immediately for the next day of vaccine distributions. 
    this->currentVaccinationDuration = 0;
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
