// Class Header Include
#include "Simulation.h"

// From the C++ Standard Library
#include <chrono>
#include <iostream>
#include <random>

int main()
{
    constexpr unsigned DAYS_TO_RUN_SIMULATION = 5;
    Simulation simulation;
    simulation.runSimulation(DAYS_TO_RUN_SIMULATION);
    return 0;
}

Simulation::Simulation() : vaccinationCenter() { }

void Simulation::runSimulation(unsigned daysToSimulate)
{
    for (size_t idx = 0; idx < daysToSimulate; idx++)
    {
        std::cout << "Simulating Day " << idx + 1 << std::endl;
        this->simulateOneDay();
    }
    vaccinationCenter.printReport();
}

void Simulation::simulateOneDay()
{
    // Seed the simulation with the number of patients that arrive within each hour time-block,
    // assuming a normal distribution around 30 arrivals/hour with a standard deviation of 1.
    const double AVERAGE_ARRIVALS_PER_HOUR = 30.0;
    const double STANDARD_DEVIATION = 1.0;
    std::default_random_engine generator;
    generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> distribution(AVERAGE_ARRIVALS_PER_HOUR, STANDARD_DEVIATION);

    // Drive the simulation, stepping hour by hour
    size_t patientId = 0;
    for (size_t i = 0; i < 12; i++)
    {
        double number = distribution(generator);
        int patientsInCurrentHour = int(round(number));

        // Create the object to model patients. Assume 20% of the population is 65 years old or over; use this
        // metric to make a randomized determination of the patient gets marked as senior vs. non-senior.
        std::uniform_int_distribution<unsigned> distribution(0, 99);
        const unsigned seniorThreshold = 20;
        for (size_t idx = 0; idx < patientsInCurrentHour; idx++)
        {
            unsigned randomValue = distribution(generator);
            if (randomValue < seniorThreshold)
            {
                this->vaccinationCenter.acceptSenior(patientId);
            }
            else
            {
                this->vaccinationCenter.acceptNonSenior(patientId);
            }
            patientId++;
        }
        this->vaccinationCenter.stepOneHour();
    }
    this->vaccinationCenter.nextDay();
}
