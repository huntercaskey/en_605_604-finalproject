#pragma once

class Patient
{
/// <summary>
/// Class representing a patient receiving a vaccination, used to record individual metrics for arrival times and 
/// times spent in various phases of the vaccination center system.
/// </summary>
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

/// <summary>
/// Subtype of a Patient object representing a senior citizen receiving a vaccination.
/// </summary>
class SeniorPatient : public Patient
{
public:
	SeniorPatient(int identifier) : Patient(identifier) { }
};

/// <summary>
/// Subtype of a Patient object representing a non-senior citizen receiving a vaccination.
/// </summary>
class NonSeniorPatient : public Patient
{
public:
	NonSeniorPatient(int identifier) : Patient(identifier) { }
};
