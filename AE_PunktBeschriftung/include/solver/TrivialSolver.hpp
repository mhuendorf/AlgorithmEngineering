#pragma once

#include <representations/Instance.hpp>
#include <representations/Solution.hpp>
#include <representations/SimpleSolution.hpp>

class TrivialSolver {
public:
    TrivialSolver() = default;

    SimpleSolution solve(Instance &instance) const;
};
