//
// Created by Marcel Hündorf on 02.11.20.
//

#include "solver/TrivialSolver.hpp"

shared_ptr<Solution> TrivialSolver::solve(Instance instance) {
    Solution sol(instance);
    for (int i = 0; i < instance.size(); ++i) {
        if (sol.wouldFit(i, Defs::TOP_LEFT)) {
            sol.placeLabel(i, Defs::TOP_LEFT);
        } else if (sol.wouldFit(i, Defs::TOP_RIGHT)) {
            sol.placeLabel(i, Defs::TOP_RIGHT);
        } else if (sol.wouldFit(i, Defs::BOTTOM_LEFT)) {
            sol.placeLabel(i, Defs::BOTTOM_LEFT);
        } else if (sol.wouldFit(i, Defs::BOTTOM_RIGHT)) {
            sol.placeLabel(i, Defs::BOTTOM_RIGHT);
        }
    }
    return make_shared<Solution>(sol);
}
