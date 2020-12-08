#include <representations/Instance.hpp>
#include <representations/Solution.hpp>

Solution::Solution(const Instance &instance1) : instance(std::make_shared<Instance>(instance1)) {
}

const Point &Solution::getPoint(int idx) const {
    return instance->getPoint(idx);
}
