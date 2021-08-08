#include "VaccinationStation.h"
#include "Patient.h"

VaccinationStation::VaccinationStation()
{
    std::default_random_engine generator;
    std::exponential_distribution<> distribution(AVERAGE_INJECTIONS_PER_HOUR);
    this->getServiceTime = std::bind(distribution, generator);
}

void VaccinationStation::performVaccination(PatientRecord& patient)
{
    double distributionSample = this->getServiceTime();
    
    // Scale to a factor of minutes within the hour, and add 1 to shift the distribution such that 1 minute is the minimum service time.
    int normalizationFactor = 60; 
    int waitTime = int(normalizationFactor * distributionSample) + 1;

    patient.setVaccinationStationServiceTime(waitTime);
}

void VaccinationStation::nextDay()
{
    lastServiceTime = 0;
}

unsigned VaccinationStation::getNextAvailableTime(unsigned elapsedTime) const
{
    return elapsedTime + lastServiceTime;
}
