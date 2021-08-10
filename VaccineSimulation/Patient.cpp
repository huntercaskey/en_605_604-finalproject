// Class Header Include
#include "Patient.h"

Patient::Patient(int identifier) : patientIdentifier(identifier) { }

void Patient::setVerificationQueueWaitTime(int verificationQueueWaitTime)
{
	this->verificationQueueWaitTime = verificationQueueWaitTime;
}

void Patient::setVaccinationStationQueueWaitTime(int vaccinationStationQueueWaitTime)
{
	this->vaccinationStationQueueWaitTime = vaccinationStationQueueWaitTime;
}

void Patient::setVaccinationStationServiceTime(int vaccinationStationServiceTime)
{
	this->vaccinationStationServiceTime = vaccinationStationServiceTime;
}

void Patient::setArrivalTime(int arrivalTime)
{
	this->arrivalTime = arrivalTime;
}

void Patient::setVaccinatedDate(int date)
{
	this->vaccinatedDate = date;
}

int Patient::getArrivalTime() const
{
	return this->arrivalTime;
}

int Patient::getVaccinatedDate() const
{
	return this->vaccinatedDate;
}

int Patient::getTotalVaccinationCenterTime() const
{
	int totalWaitTime = this->verificationQueueWaitTime + this->vaccinationStationQueueWaitTime + this->vaccinationStationServiceTime;
	return totalWaitTime;
}

int Patient::getVerificationQueueWaitTime() const
{
	return this->verificationQueueWaitTime;
}

int Patient::getVaccinationStationQueueWaitTime() const
{
	return this->vaccinationStationQueueWaitTime;
}

int Patient::getVaccinationStationServiceTime() const
{
	return this->vaccinationStationServiceTime;
}
