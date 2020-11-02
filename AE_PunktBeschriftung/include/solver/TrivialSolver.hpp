//
// Created by Marcel Hündorf on 02.11.20.
//

#ifndef UNTITLED_TRIVIALSOLVER_HPP
#define UNTITLED_TRIVIALSOLVER_HPP

#include <solver/Solver.hpp>

class TrivialSolver : Solver {
public:
    TrivialSolver() = default;

    shared_ptr<Solution> solve(Instance instance) override;
};


#endif //UNTITLED_TRIVIALSOLVER_HPP
