#include "Simulation.h"
#include "Patient.h"
#include "VaccinationCenter.h"

#include <chrono>
#include <random>
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";

    VaccinationCenter vaccinationCenter;
    std::default_random_engine generator;

    // Seed the simulation with the number of patients that arrive within each hour time-block,
    // assuming a normal distribution around 30 arrivals/hour with a standard deviation of 1.
    const double AVERAGE_ARRIVALS_PER_HOUR = 30.0;
    const double STANDARD_DEVIATION = 1.0;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> distribution(AVERAGE_ARRIVALS_PER_HOUR, STANDARD_DEVIATION);

    // Drive the simulation, stepping hour by hour
    size_t patientId = 0;
    for (size_t i = 0; i < 12; i++)
    {
        double number = distribution(generator);
        int patientsInCurrentHour = int(round(number));
        //std::cout << "Total Patients Arriving in time block " << i << " = " << patientsInCurrentHour << std::endl;


        // Create the object to model patients. Assuming 20% of the population is 65 years old or over; use this
        // metric to make a randomized determination if the patient gets marked as senior vs. non-senior.

        std::uniform_int_distribution<unsigned> distribution(0, 99);
        const unsigned seniorThreshold = 20;
        for (size_t idx = 0; idx < patientsInCurrentHour; idx++)
        {
            unsigned randomValue = distribution(generator);
            if (randomValue < seniorThreshold)
            {
                vaccinationCenter.acceptSenior(patientId);
            }
            else
            {
                vaccinationCenter.acceptNonSenior(patientId);
            }
            patientId++;
        }
        vaccinationCenter.stepOneHour();
    }
    vaccinationCenter.printReport();




    std::cout << "Goodbye World!\n";
}