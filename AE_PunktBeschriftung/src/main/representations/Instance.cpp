//
// Created by Marcel Hündorf on 26.10.20.
//

#include <iostream>
#include "Instance.hpp"
#include "Point2D.hpp"

Instance::Instance() {
}

void Instance::operator+(Point2D &point2D) {
    this->points.push_back(point2D);
}

std::ostream &operator<<(std::ostream& ostream, const Instance& instance) {
    for (auto point : instance.points) {
        ostream << point << std::endl;
    }
    return ostream;
}
