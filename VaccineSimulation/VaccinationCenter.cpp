
#include <random>

#include "VaccinationCenter.h"
#include <stdexcept>
#include <functional>

VaccinationCenter::VaccinationCenter()
{
    std::default_random_engine generator;
    std::exponential_distribution<> distribution(AVERAGE_ARRIVALS_PER_HOUR);
    this->getArrivalTime = std::bind(distribution, generator);

    for (size_t i = 0; i < NUM_VACCINATION_STATIONS; i++)
    {
        vaccinationStations[i] = VaccinationStation();
    }
}

void VaccinationCenter::acceptPatient(NonSeniorPatient& patient)
{
    std::function<void()> lambda = [&]() {
        this->nonSeniorQueue.push_back(patient);
    };
    this->processPatient(patient, lambda);
}

void VaccinationCenter::acceptPatient(SeniorPatient& patient)
{
    std::function<void()> lambda = [&]() {
        this->seniorQueue.push_back(patient);
    };
    this->processPatient(patient, lambda);
}

void VaccinationCenter::servicePendingPatients()
{
    while (!this->seniorQueue.empty())
    {
        // Get next available vaccination station, vaccinate patient
        PatientRecord& patient = this->seniorQueue.front();
        this->seniorQueue.pop_front();
        auto station = this->getNextAvailableStation();
        station.performVaccination(patient);

        // Record the queue waiting time
        unsigned vaccinatedTime = patient.getVaccinationStationServiceTime();
        unsigned queueEntryTime = patient.getVerificationQueueWaitTime() + patient.getArrivalTime();
        patient.setVaccinationStationQueueWaitTime(vaccinatedTime - queueEntryTime);

    }

    while (this->nonSeniorQueue.empty())
    {
        // Get next available vaccination station, vaccinate patient
        PatientRecord& patient = this->nonSeniorQueue.front();
        this->seniorQueue.pop_front();
        // Set queue waiting time
        auto station = this->getNextAvailableStation();
        station.performVaccination(patient);
    }
}

VaccinationStation& VaccinationCenter::getNextAvailableStation()
{
    VaccinationStation& station = this->vaccinationStations[0];
    for (const auto& vaccinationStation : this->vaccinationStations)
    {
        if (station.getNextAvailableTime(elapsedTime) < vaccinationStation.getNextAvailableTime(elapsedTime))
        {
            station = vaccinationStation;
        }
    }
    return station;
}

void VaccinationCenter::processPatient(PatientRecord& patient, std::function<void()>& queuePatientCallback)
{
    this->patientRecords.push_back(patient);

    // Calculate and set the arrival time for the new patient
    double distributionSample = this->getArrivalTime();
    // Scale to a factor of minutes within the hour, shifting by 
    int normalizationFactor = 60;
    int arrivalTimeOffset = int(round(normalizationFactor * distributionSample));
    patient.setArrivalTime(this->elapsedTime + arrivalTimeOffset);
    
    // Adjust the Vaccination Center's 'clock'
    this->elapsedTime += arrivalTimeOffset;

    // Any patients arriving after the 12-hour window are turned away.
    if (this->elapsedTime <= END_TIME_MINUTES)
    {
        // Check-in the patient
        patient.setVaccinatedDate(this->date);
        this->checkinArea.checkInPatient(patient);
        queuePatientCallback();
    }
}

void VaccinationCenter::nextDay()
{
    this->elapsedTime = 0;
    this->date++;
}


