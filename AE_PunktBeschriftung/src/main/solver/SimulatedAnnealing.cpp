//
// Created by Marcel Hündorf on 04.12.20.
//

#include <representations/BasicSolution.hpp>
#include <solver/SimulatedAnnealing.hpp>
#include <solver/TrivialSolver.hpp>
#include <random>
#include <iostream>

BasicSolution SimulatedAnnealing::solve(Instance &instance) {
    double dec2=0.999;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    BasicSolution currentSolution = getInitialSolution(instance);
    BasicSolution bestSolution = currentSolution;
    for (double t0 = T0_START; t0 >= T_MIN_1; t0 *= dec2){
        for (double t_now = t0; t_now >= T_MIN_2; t_now *= DEC_1) {
            BasicSolution newSolution = modifySolution(currentSolution, mt);
            //std::cout << t0 << "\t " << t_now << "\t " << acceptWorseSolution(1, t_now, dist(mt)) << std::endl;
            if (newSolution.size() >= currentSolution.size() ||
                acceptWorseSolution(currentSolution.size() - newSolution.size(), t_now, dist(mt))) {
                currentSolution = BasicSolution(newSolution);
                if (currentSolution.size() >= bestSolution.size()) {
                    bestSolution = currentSolution;
                }
            }
        }
    }
    return bestSolution;
}

BasicSolution SimulatedAnnealing::getInitialSolution(Instance &instance) {
    return TrivialSolver().solve(instance);
}

BasicSolution& SimulatedAnnealing::modifySolution(BasicSolution& currentSolution, const std::mt19937 &mt) {
    return currentSolution;
}

bool SimulatedAnnealing::acceptWorseSolution(int difference, double currentTemperature, double random) {
    return exp(-(difference / currentTemperature)) < random;
}
