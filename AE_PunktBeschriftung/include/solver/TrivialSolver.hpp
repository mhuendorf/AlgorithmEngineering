#pragma once

#include <representations/Instance.hpp>
#include <representations/SolutionWithGraph.hpp>

class TrivialSolver {
public:
    TrivialSolver() = default;

    SolutionWithGraph solve(Instance& instance) const;
};
