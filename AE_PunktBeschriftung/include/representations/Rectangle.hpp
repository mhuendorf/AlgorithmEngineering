//
// Created by Marcel Hündorf on 27.10.20.
//

#ifndef UNTITLED_RECTANGLE_HPP
#define UNTITLED_RECTANGLE_HPP

#include <iostream>
#include <representations/Point2D.hpp>

using namespace std;

class Rectangle {
private:
    shared_ptr<Point2D> topLeft;
    shared_ptr<Point2D> topRight;
    shared_ptr<Point2D> bottomRight;
    shared_ptr<Point2D> bottomLeft;

public:
    Rectangle(Point2D &topLeft, Point2D &bottomRight);
    bool isOverlapping(Rectangle &rectangle);
    Point2D getTopLeft();
    Point2D getTopRight();
    Point2D getBottomLeft();
    Point2D getBottomRight();
};


#endif //UNTITLED_RECTANGLE_HPP
