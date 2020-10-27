//
// Created by Marcel Hündorf on 26.10.20.
//

#include "../../include/representations/Point2D.hpp"
#include "../../include/representations/Box.hpp"

#include <iostream>
#include <iomanip>


Point2D::Point2D(int x, int y, Box* box) {
    this->x = x;
    this->y = y;
    this->box = box;
}

std::ostream &operator<<(std::ostream &ostream, const Point2D &point2D) {
    return ostream << std::setw(6) << point2D.x << std::setw(6) << point2D.y << *point2D.box;
}
