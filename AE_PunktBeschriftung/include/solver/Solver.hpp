//
// Created by Marcel Hündorf on 27.10.20.
//

#ifndef UNTITLED_SOLVER_HPP
#define UNTITLED_SOLVER_HPP

#include <representations/Solution.hpp>

class Solver {
public:
    virtual shared_ptr<Solution> solve(Instance instance) = 0;
};

#endif //UNTITLED_SOLVER_HPP
