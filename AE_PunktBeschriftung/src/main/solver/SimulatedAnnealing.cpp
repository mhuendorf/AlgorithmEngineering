#include <representations/BasicSolution.hpp>
#include <solver/SimulatedAnnealing.hpp>
#include <random>
#include <iostream>

SimulatedAnnealingSolution SimulatedAnnealing::solve(Instance &instance) {
    double dec2=0.95;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> distReal(0.0, 1.0);
    std::uniform_int_distribution<int> distInt;
    SimulatedAnnealingSolution currentSolution = getInitialSolution(instance);
    SimulatedAnnealingSolution bestSolution = currentSolution;

    std::cout << "cooling down..." << std::endl;
    for (double t0 = T0_START; t0 >= T_MIN_1; t0 *= dec2) {
        std::cout << "\rtemperature: " << t0;
        std::cout.flush();
        for (double t_now = t0; t_now >= T_MIN_2; t_now *= DEC_1) {

            SimulatedAnnealingSolution newSolution(currentSolution);
            newSolution.changePlacement(distInt(mt)%newSolution.size(), distInt(mt));
            if (newSolution.getSolutionScore() <= currentSolution.getSolutionScore() ||
                acceptWorseSolution( newSolution.getSolutionScore() - currentSolution.getSolutionScore(), t_now, distReal(mt))) {
                currentSolution = SimulatedAnnealingSolution(newSolution);
                if (currentSolution.getSolutionScore() <= bestSolution.getSolutionScore()) {
                    bestSolution = currentSolution;
                }
            }
        }
    }
    std::cout << "\rfinished... " << std::endl;

    // fix solution
    bestSolution.fixSolution();
    return bestSolution;
}

SimulatedAnnealingSolution SimulatedAnnealing::getInitialSolution(Instance &instance) {
    SimulatedAnnealingSolution solution = SimulatedAnnealingSolution(instance);
    solution.initSolution();
    return solution;
}

bool SimulatedAnnealing::acceptWorseSolution(double difference, double currentTemperature, double random) {
    return exp(-(difference / currentTemperature)) > random;
}
