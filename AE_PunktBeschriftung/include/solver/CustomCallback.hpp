#pragma once 

#include <solver/TrivialSolver.hpp>
#include <representations/BasicSolution.hpp>
#include <representations/Instance.hpp>

#include "gurobi_c++.h"


class CustomCallback : public GRBCallback {

private: 

    Instance& instance;
    TrivialSolver heuristic;
    GRBModel& model;

    int heuristicInsertions;

    void heuristicSolution();
    void cut();

protected:

    void callback();

public:

    CustomCallback(Instance& instance, GRBModel& model);

};