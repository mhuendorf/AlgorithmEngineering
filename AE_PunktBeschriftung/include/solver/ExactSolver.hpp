#pragma once

#include <representations/Instance.hpp>
#include <representations/BasicSolution.hpp>

class ExactSolver {

public:

ExactSolver() {};

BasicSolution solve(const Instance& instance);

};