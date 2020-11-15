#pragma once

#include <representations/Instance.hpp>
#include <representations/Solution.hpp>

class TrivialSolver {
public:
    TrivialSolver() = default;

    Solution solve(Instance& instance) const;
};
