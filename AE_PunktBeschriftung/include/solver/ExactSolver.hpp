#pragma once

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>
#include <solver/Solver.hpp>

class ExactSolver : public Solver {

private:

    Solver& heuristic;

    //void separation();

public:

    ExactSolver(Solver& solver) : heuristic(solver) {};

    BasicSolution solve(Instance& instance) override;

};