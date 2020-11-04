#include <representations/Instance.hpp>
#include <representations/PointWithLabel.hpp>

#include <iostream>
#include <memory>
#include <string>
using std::string;

#include <vector>
using std::vector;

Instance::Instance() {
    std::cout << "Creating Instance" << std::endl;
}

void Instance::reserve(int num) {
    this->points.reserve(num);
}

void Instance::operator+(std::shared_ptr<PointWithLabel> point2D) {
    this->points.push_back(std::move(point2D));
}

std::ostream &operator<<(std::ostream &ostream, const Instance &instance) {
    for (auto const &point : instance.points) {
        ostream << *point << std::endl;
    }
    return ostream;
}

int Instance::size() {
    return this->points.size();
}

std::shared_ptr<PointWithLabel> Instance::getPoint(int idx) {
    std::cout << "size: " << points.size() << std::endl;
    return points.at(idx);
}
