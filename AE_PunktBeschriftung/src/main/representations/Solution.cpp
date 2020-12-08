#include <representations/Instance.hpp>
#include <representations/Solution.hpp>
#include <memory>

Solution::Solution(const Instance &instance1) : instance(instance1) {
}

const Point &Solution::getPoint(int idx) const {
    return instance.getPoint(idx);
}
