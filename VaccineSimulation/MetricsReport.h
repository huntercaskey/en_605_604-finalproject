#pragma once

#include <string>

class MetricsReport
{
public:
	MetricsReport(unsigned simulationDays, 
				  unsigned totalCustomers, 
				  double averageCustomersPerDay, 
				  double averageTotalTime, 
				  double averageVerificationQueueWaitTime, 
				  double averageVaccinationQueueWaitTime);

	std::string toString();
private:
	unsigned simulationDays;
	unsigned totalCustomers;
	double averageCustomersPerDay;
	double averageTotalTime;
	double averageVerificationQueueWaitTime;
	double averageVaccinationQueueWaitTime;
};

