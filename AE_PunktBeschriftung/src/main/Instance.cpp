//
// Created by Marcel Hündorf on 26.10.20.
//

#include <iostream>
#include "../../include/representations/Instance.hpp"
#include "../../include/representations/Point2D.hpp"

Instance::Instance() {
}

void Instance::operator+(Point2D &point2D) {
    this->points.push_back(point2D);
}

std::ostream &operator<<(std::ostream& ostream, const Instance& instance) {
    ostream << instance.points.size() << std::endl;
    for (auto point : instance.points) {
        ostream << point << std::endl;
    }
    return ostream;
}

int Instance::size() {
    return this->points.size();
}

std::unique_ptr<std::vector<Point2D>> Instance::getPoints() {
    return std::unique_ptr<std::vector<Point2D>>(&this->points);
}
