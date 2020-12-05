//
// Created by Marcel Hündorf on 04.12.20.
//

#ifndef LABEL_MAP_SIMULATEDANNEALING_HPP
#define LABEL_MAP_SIMULATEDANNEALING_HPP


#include <representations/Solution.hpp>
#include <random>

class SimulatedAnnealing {
private:
    constexpr static const double DEC_1 = 0.995;
    constexpr static const double T0_START = 100;
    constexpr static const double T_MIN_1 = 1;
    constexpr static const double T_MIN_2 = 0.01;

    static BasicSolution getInitialSolution(Instance& instance);

    static BasicSolution& modifySolution(BasicSolution& sharedSolution,
                                                         const std::__1::mersenne_twister_engine<uint_fast32_t, 32, 624, 397, 31, 0x9908b0df, 11, 0xffffffff, 7, 0x9d2c5680, 15, 0xefc60000, 18, 1812433253> &mt);

    static bool acceptWorseSolution(int difference, double currentTemperature, double random);

public:
    static BasicSolution solve(Instance& instance);

};


#endif //LABEL_MAP_SIMULATEDANNEALING_HPP
