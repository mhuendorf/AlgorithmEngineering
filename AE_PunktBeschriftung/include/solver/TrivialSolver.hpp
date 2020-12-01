#pragma once

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>

class TrivialSolver {
public:
    TrivialSolver() = default;

    BasicSolution solve(Instance& instance) const;
};
