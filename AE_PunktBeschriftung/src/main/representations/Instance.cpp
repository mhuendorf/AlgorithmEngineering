//
// Created by Marcel Hündorf on 26.10.20.
//

#include <iostream>
#include "Instance.hpp"
#include "Point2D.hpp"
#include <memory>

Instance::Instance() {
}

void Instance::operator+(std::unique_ptr<Point2D> point2D) {
    this->points.push_back(std::move(point2D));
}

std::ostream &operator<<(std::ostream& ostream, const Instance& instance) {
    for (auto const& point : instance.points) {
        ostream << *point << std::endl;
    }
    return ostream;
}
