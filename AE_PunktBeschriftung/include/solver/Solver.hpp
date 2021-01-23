#pragma once

#include <representations/Solution.hpp>
#include <representations/BasicSolution.hpp>
#include <representations/Instance.hpp>

class Solver {

public:

    Solver() {};

    // needs to return a pointer, because it's impossible to return an abstract class by value
    // virtual std::shared_ptr<Solution> solve(Instance& instance) = 0;

    // doing this for now because it is simpler, no pointers needed
    virtual BasicSolution solve(Instance& instance) = 0;
};