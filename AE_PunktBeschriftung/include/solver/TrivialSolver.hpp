#pragma once

#include <representations/Instance.hpp>

class TrivialSolver {
public:
    TrivialSolver() = default;

    void solve(Instance& instance) const;
};
