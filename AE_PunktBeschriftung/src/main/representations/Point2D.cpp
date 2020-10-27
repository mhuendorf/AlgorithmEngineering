//
// Created by Marcel Hündorf on 26.10.20.
//

#include "Point2D.hpp"
#include "Box.hpp"

#include <iostream>
#include <iomanip>


Point2D::Point2D(int x, int y, std::unique_ptr<Box> boxParam) : x(x), y(y), box(std::move(boxParam)) 
{

}

std::ostream &operator<<(std::ostream &ostream, const Point2D &point2D) {
    return ostream << std::setw(6) << point2D.x << std::setw(6) << point2D.y << *point2D.box;
}
