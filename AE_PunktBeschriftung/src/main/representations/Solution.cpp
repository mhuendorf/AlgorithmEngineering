//
// Created by Marcel Hündorf on 16.11.20.
//

#include "representations/Solution.hpp"


Solution::Solution(Instance &instance1) : instance(instance1) {
}

Point Solution::getPoint(int idx) const {
    return instance.getPoint(idx);
}

