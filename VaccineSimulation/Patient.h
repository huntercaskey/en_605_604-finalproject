#pragma once

class Patient
{
public:
	Patient(int identifier);
	Patient() = delete;
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

class SeniorPatient : public Patient
{
public:
	SeniorPatient(int identifier) : Patient(identifier) { }
};

class NonSeniorPatient : public Patient
{
public:
	NonSeniorPatient(int identifier) : Patient(identifier) { }
};
