#include <representations/Point.hpp>

#include <iostream>
#include <stdexcept>

#include <string>
using std::string;

#include <vector>
using std::vector;

using Point2D = std::tuple< int, int >; // contains the X and Y coordinate of a point in 2D space

// Constructor: initializes points and reserves memory
// initializing coordinates to 0,0, which is meaningless anyway as long as the placement is 0 as well
Point::Point(int x, int y, int width, int height, string label) 
        : x(x), y(y), width(width), height(height), label(label), placement(NOT_PLACED), upperLeft{0,0}, lowerRight{0,0} {
}

int Point::getX() const {
    return x;
}

int Point::getY() const {
    return y;
}

string Point::getName() const {
    return label;
}

void Point::setPlacement(Corner placement) {

    this->placement = placement;

    std::tuple<Point2D, Point2D> coords = this->getCoordsForPlacement(placement);

    this->upperLeft = std::get<0>(coords);
    this->lowerRight = std::get<1>(coords);

}

const Point::Corner& Point::getPlacement() const {
    return placement;
}

std::ostream& operator<<(std::ostream& ostream, const Point& point) {

    ostream << point.getX() << " " 
            << point.getY() << " " 
            << point.width << " "
            << point.height << " " 
            << point.getName() << " ";

    if(point.placement != Point::NOT_PLACED) {
        ostream << "1 "
                << std::get<0>(point.upperLeft) << " "
                << std::get<1>(point.upperLeft) << " ";
    } else {
        ostream << "0 0 0";
    }
    
    return ostream;
}


std::tuple< Point2D, Point2D > Point::getCoordsForPlacement(Corner corner) const {

    // calculating coords of upper left corner of box
    int uLX = (corner == TOP_LEFT || corner == BOTTOM_LEFT) ? x : x - width;
    int uLY = (corner == TOP_LEFT || corner == TOP_RIGHT) ? y : y + height;

    // calculating coords of lower right corner of box
    int lRX = (corner == BOTTOM_RIGHT || corner == TOP_RIGHT) ? x : x + width;
    int lRY = (corner == BOTTOM_RIGHT || corner == BOTTOM_LEFT) ? y : y - height;

    Point2D upperLeft = std::tuple< int, int >(uLX, uLY);
    Point2D lowerRight = std::tuple< int, int >(lRX, lRY);

    return std::tuple< Point2D, Point2D >(upperLeft, lowerRight);
}

bool Point::checkCollision(const Point& other) const {
    return this->checkCollision(other, other.getPlacement());
}

// two rectangles do not collide if either one is above the other or besides the other
bool Point::checkCollision(const Point& other, Corner corner) const {

    if(this->placement == NOT_PLACED) throw std::invalid_argument("Cannot check collision against unlabeled point");

    std::tuple< Point2D, Point2D > coords = other.getCoordsForPlacement(corner);

    Point2D other_uL = std::get<0>(coords);
    Point2D other_lR = std::get<1>(coords);

    // in both directions, check if one is above the other
    if(std::get<1>(other_lR) >= std::get<1>(this->upperLeft)
            || std::get<1>(this->lowerRight) >= std::get<1>(other_uL)) {
        return false;
    }

    // in both directions, check if one is besides the other
    if(std::get<0>(other_lR) <= std::get<0>(this->upperLeft)
            || std::get<0>(this->lowerRight) <= std::get<0>(other_uL)) {
        return false;
    }

    // if none of that was the case, they do overlap somehow
    return true;

}