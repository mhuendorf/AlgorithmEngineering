#include "representations/Solution.hpp"

Solution::Solution(Instance &instance1) : instance(instance1) {
}

const Point &Solution::getPoint(int idx) const {
    return instance.getPoint(idx);
}
