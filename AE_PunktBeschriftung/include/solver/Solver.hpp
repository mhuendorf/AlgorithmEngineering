#ifndef UNTITLED_SOLVER_HPP
#define UNTITLED_SOLVER_HPP

#include <representations/Solution.hpp>

class Solver {
public:
    virtual shared_ptr<Solution> solve(const Instance& instance) = 0;
};

#endif //UNTITLED_SOLVER_HPP
