#include <representations/Instance.hpp>
#include <representations/Solution.hpp>

Solution::Solution(const Instance &instance) : instance(instance) {
}

const Point &Solution::getPoint(int idx) const {
    return instance.getPoint(idx);
}
