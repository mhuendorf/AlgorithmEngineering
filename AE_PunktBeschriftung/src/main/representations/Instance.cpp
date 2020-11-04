#include <representations/Instance.hpp>
#include <representations/PointWithLabel.hpp>

#include <iostream>
#include <memory>
#include <string>
using std::string;

#include <vector>
using std::vector;

Instance::Instance() {
}

void Instance::reserve(int num) {
    this->points.reserve(num);
}

void Instance::operator+(std::shared_ptr<PointWithLabel> point2D) {
    this->points.push_back(std::move(point2D));
}

std::ostream &operator<<(std::ostream &ostream, const Instance& instance) {
    for (auto const &point : instance.points) {
        ostream << *point << std::endl;
    }
    return ostream;
}

int Instance::size() const {
    return this->points.size();
}

const std::shared_ptr<PointWithLabel>& Instance::getPoint(int idx) const {
    return points.at(idx);
}