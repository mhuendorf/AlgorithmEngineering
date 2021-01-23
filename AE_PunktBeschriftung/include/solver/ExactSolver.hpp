#pragma once

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/Solver.hpp>

class ExactSolver : public Solver {

private:

public:

    ExactSolver(){};

    BasicSolution solve(Instance& instance) override;

};