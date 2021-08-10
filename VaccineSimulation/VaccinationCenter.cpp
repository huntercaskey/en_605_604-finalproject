// Class Header Include
#include "VaccinationCenter.h"

// From the C++ Standard Library
#include <functional>
#include <iostream>
#include <limits.h>
#include <random>

// Local Includes
#include "MetricsReport.h"


VaccinationCenter::VaccinationCenter()
{
    // Create the generator used to derive arrival time samples.
    std::default_random_engine generator;
    std::exponential_distribution<> exponential_distribution(AVERAGE_ARRIVALS_PER_HOUR);
    this->getArrivalTime = std::bind(exponential_distribution, generator);

    // Create the generator used to verification queue wait time samples.
    std::uniform_int_distribution<int> uniform_distribution(MIN_WAIT_TIME_MINUTES, MAX_WAIT_TIME_MINUTES);
    this->getWaitTime = std::bind(uniform_distribution, generator);

    // Create the vaccination stations and store them for future use.
    for (size_t i = 0; i < NUM_VACCINATION_STATIONS; i++)
    {
        vaccinationStations[i] = VaccinationStation(i);
    }
}

void VaccinationCenter::acceptNonSenior(int patientId)
{
    // Any patients arriving after the 12-hour window are turned away.
    if (this->elapsedTime <= END_TIME_MINUTES)
    {
        NonSeniorPatient patient(patientId);
        this->patientRecords.push_back(patient);
        size_t position = this->patientRecords.size() - 1;
        this->nonSeniorQueue.push_back(position);
        this->newPatients.push_back(position);
    }
}

void VaccinationCenter::acceptSenior(int patientId)
{
    // Any patients arriving after the 12-hour window are turned away.
    if (this->elapsedTime <= END_TIME_MINUTES)
    {
        SeniorPatient patient(patientId);
        this->patientRecords.push_back(patient);
        size_t position = this->patientRecords.size() - 1;
        this->seniorQueue.push_back(position);
        this->newPatients.push_back(position);
    }
}

void VaccinationCenter::stepOneHour()
{
    // After 12 hours, the vaccination center is closed and shall not accept any more patients. 
    unsigned nextHourMark;
    if (this->elapsedTime > END_TIME_MINUTES)
    {
        return;
    }
    else if (this->elapsedTime == END_TIME_MINUTES)
    {
        // If the vaccination center is about to close (the last minute), all pending patients should be serviced no matter how long it takes. 
        nextHourMark = UINT_MAX;
    }
    else
    {
        // Try to service as many patients as possible within a 1-hour timeblock.
        nextHourMark = this->elapsedTime + 60;
        
        // Generate all of the arrival and check-in times up front and sort them
        std::list<int> arrivalTimes;
        std::list<int> waitTimes;
        for (auto patient : this->newPatients)
        {
            // Calculate and set the arrival time for the new patient
            double distributionSample = this->getArrivalTime();
            // Scale to a factor of minutes within the hour, shifting by 
            int normalizationFactor = 60;
            int arrivalTimeOffset = int(round(normalizationFactor * distributionSample));
            int arrivalTime = this->elapsedTime + arrivalTimeOffset;
            arrivalTimes.push_back(arrivalTime);

            int waitTime = this->getWaitTime();
            waitTimes.push_back(waitTime);
        }
        arrivalTimes.sort();
        waitTimes.sort();

        // Initiate the check-in procedure for all patients that arrived within the current 1-hour timeblock.
        while (!this->newPatients.empty())
        {
            size_t patientIndex = this->newPatients.front();
            this->newPatients.pop_front();
            Patient& patient = this->patientRecords.at(patientIndex);
        
            patient.setArrivalTime(arrivalTimes.front());
            patient.setVerificationQueueWaitTime(waitTimes.front());
            arrivalTimes.pop_front();
            waitTimes.pop_front();
            
            // Check-in the patient
            patient.setVaccinatedDate(this->date);
        }
    }

    // Perform operation minute-by-minute, attempting to optimize use of all vaccination stations 
    // to administer as many vaccines as possible to patients, prioritizing senior patients first.
    while (this->elapsedTime < nextHourMark)
    {
        // Attempt to service as many waiting senior patients as possible.
        while (!this->seniorQueue.empty())
        {
            // Get the patient who is next in line
            size_t patientIndex = this->seniorQueue.front();
            Patient& patient = this->patientRecords.at(patientIndex);

            // Verify the patient has gone-through check-in before attempting to service them
            unsigned vaccineQueueEntryTime = patient.getArrivalTime() + patient.getVerificationQueueWaitTime();
            if (vaccineQueueEntryTime > this->elapsedTime)
            {
                // If this patient hasn't been checked in, then none of the other patients after them have, try again at teh next time step.
                break;
            }

            VaccinationStation* station = this->getNextAvailableStation();

            if (nullptr != station)
            {
                // Patient is servicable, remove them from the queue.
                this->seniorQueue.pop_front();
                
                // Record how long the patient was waiting in the queue for.
                unsigned vaccinationQueueWaitTime = this->elapsedTime - vaccineQueueEntryTime;
                patient.setVaccinationStationQueueWaitTime(vaccinationQueueWaitTime);
                
                // Vaccinate the patient.
                station->performVaccination(patient, this->elapsedTime);
            }
            else
            {
                // No saccination stations are open, continue and try again at the next time step.
                break;
            }
        }

        // Now try to do the same with non-senior patients
        while (!this->nonSeniorQueue.empty())
        {
            // Get the patient who is next in line
            size_t patientIndex = this->nonSeniorQueue.front();
            Patient& patient = this->patientRecords.at(patientIndex);

            // Verify the patient has gone-through check-in before attempting to service them
            unsigned vaccineQueueEntryTime = patient.getArrivalTime() + patient.getVerificationQueueWaitTime();
            if (vaccineQueueEntryTime > this->elapsedTime)
            {
                // If this patient hasn't been checked in, then none of the other patients after them have, try again at teh next time step.
                break;
            }

            VaccinationStation* station = this->getNextAvailableStation();

            if (nullptr != station)
            {
                // Patient is servicable, remove them from the queue.
                this->nonSeniorQueue.pop_front();

                // Record how long the patient was waiting in the queue for.
                unsigned vaccinationQueueWaitTime = this->elapsedTime - vaccineQueueEntryTime;
                patient.setVaccinationStationQueueWaitTime(vaccinationQueueWaitTime);

                // Vaccinate the patient.
                station->performVaccination(patient, this->elapsedTime);
            }
            else
            {
                // No saccination stations are open, continue and try again at the next time step.
                break;
            }
        }
        this->elapsedTime++;
    }
}

VaccinationStation* VaccinationCenter::getNextAvailableStation()
{
    auto isAvailable = [&](VaccinationStation& station)
    {
        return station.isAvailable(this->elapsedTime);
    };

    // Find an available vaccine station if one exists.
    std::array<VaccinationStation, NUM_VACCINATION_STATIONS>::iterator it;
    it = std::find_if(this->vaccinationStations.begin(), this->vaccinationStations.end(), isAvailable);

    // Didn't find an available station, break from the loop and try again at the next time increment.
    if (it == std::end(this->vaccinationStations))
    {
        return nullptr;
    }

    // A station was found, return the reference to it.
    VaccinationStation& station = *it;
    return &station;
}

void VaccinationCenter::nextDay()
{
    // Update the time-tracking variables.
    this->elapsedTime = 0;
    this->date++;

    // Clear out any patients that haven't been serviced (this should be redundant, but better to be safe than sorry). 
    this->seniorQueue.clear();
    this->nonSeniorQueue.clear();
    this->newPatients.clear();
}

void VaccinationCenter::printReport()
{
    unsigned simulationDays = this->date + 1;
    unsigned totalCustomers = this->patientRecords.size();
    unsigned averageCustomersPerDay = totalCustomers / simulationDays;

    unsigned totalPatientTime = 0;
    unsigned totalVerificationQueueWaitTime = 0;
    unsigned totalVaccinationQueueWaitTime = 0;

    // Gather the total times that all patients spent within the system, and for the time spent in waiting queues.
    for (Patient& patient : this->patientRecords)
    {
        totalPatientTime += patient.getTotalVaccinationCenterTime();
        totalVerificationQueueWaitTime += patient.getVerificationQueueWaitTime();
        totalVaccinationQueueWaitTime += patient.getVerificationQueueWaitTime();
    }

    double averageTotalTime = totalPatientTime / totalCustomers;
    double averageVerificationQueueWaitTime = totalVerificationQueueWaitTime / totalCustomers;
    double averageVaccinationQueueWaitTime = totalVaccinationQueueWaitTime / totalCustomers;

    MetricsReport report(simulationDays, totalCustomers, averageCustomersPerDay, averageTotalTime, averageVerificationQueueWaitTime, averageVaccinationQueueWaitTime);
    std::cout << report.toString();
}
