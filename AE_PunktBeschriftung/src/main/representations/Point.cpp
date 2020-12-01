#include <representations/Point.hpp>

#include <iostream>
#include <stdexcept>

#include <string>
using std::string;

#include <vector>
using std::vector;

// Constructor: initializes points and reserves memory
// initializing coordinates to 0,0, which is meaningless anyway as long as the placement is 0 as well
Point::Point(int idx, long x, long y, long width, long height, string label) 
        : idx(idx), x(x), y(y), width(width), height(height), label(label) {
}

int Point::getIdx() const {
    return idx;
}

long Point::getX() const {
    return x;
}

long Point::getY() const {
    return y;
}

string Point::getName() const {
    return label;
}

const std::vector<Point::Ptr>& Point::getNeighbours() const {
    return neighbours;
}

void Point::addNeighbour(Point::Ptr other) {
    neighbours.push_back(other);
}

std::ostream& operator<<(std::ostream& ostream, const Point& point) {

    ostream << point.getX() << " " 
            << point.getY() << " " 
            << point.width << " "
            << point.height << " " 
            << point.getName() << " ";

    return ostream;
}

Point::Rectangle Point::getBigRectangle() const {

    long uLX = x-width;
    long uLY = y+height;
    long lRX = x+width; 
    long lRY = y-height;

    return Rectangle(Point2D(uLX, uLY), Point2D(lRX, lRY));
}

bool Point::couldCollide(const Point& other) const {
    return checkCollision(getBigRectangle(), other.getBigRectangle());
}

Point::Rectangle Point::getCoordsForPlacement(Corner corner) const {

    // calculating coords of upper left corner of box
    long uLX = (corner == TOP_LEFT || corner == BOTTOM_LEFT) ? x : x - width;
    long uLY = (corner == TOP_LEFT || corner == TOP_RIGHT) ? y : y + height;

    // calculating coords of lower right corner of box
    long lRX = (corner == BOTTOM_RIGHT || corner == TOP_RIGHT) ? x : x + width;
    long lRY = (corner == BOTTOM_RIGHT || corner == BOTTOM_LEFT) ? y : y - height;

    Point2D upperLeft(uLX, uLY);
    Point2D lowerRight(lRX, lRY);

    return Rectangle(upperLeft, lowerRight);
}

bool Point::checkCollision(Rectangle rect1, Rectangle rect2) {

    // extract the points of upper Left and lower Right from the rectangles
    Point2D a_uL = std::get<0>(rect1);
    Point2D a_lR = std::get<1>(rect1);
    Point2D b_uL = std::get<0>(rect2);
    Point2D b_lR = std::get<1>(rect2);

    // in both directions, check if one is besides the other
    if(std::get<0>(a_lR) <= std::get<0>(b_uL)
            || std::get<0>(b_lR) <= std::get<0>(a_uL)) {
        return false;
    }

    // in both directions, check if one is above the other
    if(std::get<1>(a_lR) >= std::get<1>(b_uL)
            || std::get<1>(b_lR) >= std::get<1>(a_uL)) {
        return false;
    }

    // if none of that was the case, they do overlap somehow
    return true;
}
