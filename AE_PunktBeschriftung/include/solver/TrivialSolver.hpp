#pragma once

#include <solver/Solver.hpp>
#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>

class TrivialSolver : public Solver {

public:

    TrivialSolver() = default;

    BasicSolution solve(Instance& instance) override;
};
