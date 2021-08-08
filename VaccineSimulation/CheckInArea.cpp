#include <stdexcept>

#include "CheckInArea.h"

CheckInArea::CheckInArea() 
{
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(MIN_WAIT_TIME_MINUTES, MAX_WAIT_TIME_MINUTES);
    this->getWaitTime = std::bind(distribution, generator);
    this->queue = std::list<std::reference_wrapper<PatientRecord>>();
}

void CheckInArea::checkInPatient(PatientRecord& patient)
{
    patient.setVerificationQueueWaitTime(this->getWaitTime());
}
