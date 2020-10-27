//
// Created by Marcel Hündorf on 27.10.20.
//

#include "../../include/representations/Solution.hpp"

Solution::Solution(Instance &instance) {
    this->instance = std::unique_ptr<Instance>(&instance);
    for (int i = 0; i < this->instance->size(); ++i) {
        this->boxPlacements.push_back(notPLaced);
    }
}

bool Solution::isFeasible() {
    return false;
}
