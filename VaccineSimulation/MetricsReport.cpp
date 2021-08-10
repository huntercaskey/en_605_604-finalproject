#include "MetricsReport.h"

#include <sstream>

MetricsReport::MetricsReport(unsigned simulationDays, 
                             unsigned totalCustomers, 
                             double averageCustomersPerDay, 
                             double averageTotalTime, 
                             double averageVerificationQueueWaitTime,
                             double averageVaccinationQueueWaitTime)
    : simulationDays(simulationDays)
    , totalCustomers(totalCustomers)
    , averageCustomersPerDay(averageCustomersPerDay)
    , averageTotalTime(averageTotalTime)
    , averageVerificationQueueWaitTime(averageVerificationQueueWaitTime)
    , averageVaccinationQueueWaitTime(averageVaccinationQueueWaitTime)
{
}

std::string MetricsReport::toString()
{
    std::stringstream ss;
    ss << "==== Metrics Report for running the Vaccine Center Simulation " << simulationDays << "Days ====" << std::endl;
    ss << "Total Number of Customer Serviced: " << totalCustomers << std::endl;
    ss << "Average Number of Customers Serviced Per Day: " << averageCustomersPerDay << std::endl;
    ss << "Average Total Time in System (Queue Time + Service Time): " << averageTotalTime << std::endl;
    ss << "Average Verification Queue Wait Time: " << averageVerificationQueueWaitTime << std::endl;
    ss << "Average Vaccination Queue Wait Time: " << averageVaccinationQueueWaitTime << std::endl;
    return ss.str();
}
