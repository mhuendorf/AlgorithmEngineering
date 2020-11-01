//
// Created by Marcel Hündorf on 26.10.20.
//

#include <representations/Instance.hpp>
#include <representations/PointWithLabel.hpp>

#include <iostream>
#include <memory>

Instance::Instance() {
}

void Instance::operator+(std::shared_ptr<PointWithLabel> point2D) {
    this->points.push_back(std::move(point2D));
}

std::ostream &operator<<(std::ostream& ostream, const Instance& instance) {
    for (auto const& point : instance.points) {
        ostream << *point << std::endl;
    }
    return ostream;
}

int Instance::size() {
    return this->points.size();
}

std::shared_ptr<PointWithLabel> Instance::getPoint(int idx) {
    return points.at(idx);
}
