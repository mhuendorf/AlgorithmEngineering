//
// Created by Marcel Hündorf on 27.10.20.
//

#include <representations/Rectangle.hpp>

Rectangle::Rectangle(Point2D &topLeft, Point2D &bottomRight) {
    this->topLeft = make_shared<Point2D>(topLeft);
    this->bottomRight = make_shared<Point2D>(bottomRight);
    int width = bottomRight.x - topLeft.x;
    int height = topLeft.y - bottomRight.y;

    Point2D rightTop(topLeft.x + width, topLeft.y);
    Point2D leftBottom(topLeft.x, topLeft.y+height);
    this->topRight = shared_ptr<Point2D>(&rightTop);
    this->bottomLeft = shared_ptr<Point2D>(&leftBottom);
}

bool Rectangle::isOverlapping(Rectangle &rectangle) {
    // If one rectangle is on left side of other
    if (topLeft->x >= rectangle.bottomRight->x || bottomRight->x <= rectangle.topLeft->x)
        return false;

    // If one rectangle is above other
    if (topLeft->y <= rectangle.bottomRight->y || bottomRight->y >= rectangle.topLeft->y)
        return false;
    return true;
}

Point2D Rectangle::getTopLeft() {
    return *this->topLeft;
}

Point2D Rectangle::getTopRight() {
    return *this->topRight;
}

Point2D Rectangle::getBottomLeft() {
    return *this->bottomLeft;
}

Point2D Rectangle::getBottomRight() {
    return *this->bottomRight;
}

