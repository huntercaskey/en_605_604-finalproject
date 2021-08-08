#include "Patient.h"

PatientRecord::PatientRecord(int identifier) : patientIdentifier(identifier) { }

void PatientRecord::setVerificationQueueWaitTime(int verificationQueueWaitTime)
{
	this->verificationQueueWaitTime = verificationQueueWaitTime;
}

void PatientRecord::setVaccinationStationQueueWaitTime(int vaccinationStationQueueWaitTime)
{
	this->vaccinationStationQueueWaitTime = vaccinationStationQueueWaitTime;
}

void PatientRecord::setVaccinationStationServiceTime(int vaccinationStationServiceTime)
{
	this->vaccinationStationServiceTime = vaccinationStationServiceTime;
}

void PatientRecord::setArrivalTime(int arrivalTime)
{
	this->arrivalTime = arrivalTime;
}

void PatientRecord::setVaccinatedDate(int date)
{
	this->vaccinatedDate = date;
}

int PatientRecord::getArrivalTime() const
{
	return this->arrivalTime;
}

int PatientRecord::getVaccinatedDate() const
{
	return this->vaccinatedDate;
}

int PatientRecord::getTotalVaccinationCenterTime() const
{
	int totalWaitTime = this->verificationQueueWaitTime + this->vaccinationStationQueueWaitTime + this->vaccinationStationServiceTime;
	return totalWaitTime;
}

int PatientRecord::getVerificationQueueWaitTime() const
{
	return this->verificationQueueWaitTime;
}

int PatientRecord::getVaccinationStationQueueWaitTime() const
{
	return this->vaccinationStationQueueWaitTime;
}

int PatientRecord::getVaccinationStationServiceTime() const
{
	return this->vaccinationStationServiceTime;
}
