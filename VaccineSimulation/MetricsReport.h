#pragma once

// From the C++ Standard Library
#include <string>

/// <summary>
/// Class encapsulating the overall metrics of the performance of a VaccinationCenter up to the current point in time.
/// </summary>
class MetricsReport
{
public:
	/// <summary>
	/// Generates a report object.
	/// </summary>
	/// <param name="operationalDays">The number of days the vaccination center has been running up until this point.</param>
	/// <param name="totalCustomers">The total number of patients that have been accepted by the vaccine center so far.</param>
	/// <param name="averageCustomersPerDay">The average number of patients that have been processed by the vaccine center each day</param>
	/// <param name="averageTotalTime">The average total amount of time each patient has spent within the vaccine center.</param>
	/// <param name="averageVerificationQueueWaitTime">The average time each patient has spent waiting in the check-in/verification queue.</param>
	/// <param name="averageVaccinationQueueWaitTime">The average time each patient has spent waiting in their respective vaccination queue.</param>
	MetricsReport(unsigned operationalDays, 
				  unsigned totalCustomers, 
				  double averageCustomersPerDay, 
				  double averageTotalTime, 
				  double averageVerificationQueueWaitTime, 
				  double averageVaccinationQueueWaitTime);

	/// <summary>
	/// Generate the string representation of this class.
	/// </summary>
	/// <returns>A string containing a human-readable report of a vaccine center's performance.</returns>
	std::string toString();

private:
	unsigned operationalDays;
	unsigned totalCustomers;
	double averageCustomersPerDay;
	double averageTotalTime;
	double averageVerificationQueueWaitTime;
	double averageVaccinationQueueWaitTime;
};

