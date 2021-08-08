#pragma once

#include <string>

class PatientRecord
{
public:
	PatientRecord(int identifier);
	PatientRecord() = delete;
	void setArrivalTime(int arrivalTime);
	void setVaccinatedDate(int date);
	void setVerificationQueueWaitTime(int verificationQueueWaitTime);
	void setVaccinationStationQueueWaitTime(int vaccinationStationQueueWaitTime);
	void setVaccinationStationServiceTime(int vaccinationStationServiceTime);
	int getArrivalTime() const;
	int getTotalVaccinationCenterTime() const;
	int getVerificationQueueWaitTime() const;
	int getVaccinationStationQueueWaitTime() const;
	int getVaccinationStationServiceTime() const;
	int getVaccinatedDate() const;

private:
	int patientIdentifier;
	int arrivalTime = -1;
	int vaccinatedDate = -1;
	int verificationQueueWaitTime = -1;
	int vaccinationStationQueueWaitTime = -1;
	int vaccinationStationServiceTime = -1;
};

class SeniorPatient : public PatientRecord
{
public:
	SeniorPatient(int identifier) : PatientRecord(identifier) { }
};

class NonSeniorPatient : public PatientRecord
{
public:
	NonSeniorPatient(int identifier) : PatientRecord(identifier) { }
};
