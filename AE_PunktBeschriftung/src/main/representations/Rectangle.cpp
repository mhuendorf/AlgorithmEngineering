//
// Created by Marcel Hündorf on 27.10.20.
//

#include <representations/Rectangle.hpp>

Rectangle::Rectangle(int x1, int y1, int x2, int y2) :
        topLeft(x1, y1), topRight(x2, y1), bottomLeft(x1, y2), bottomRight(x2, y2) {
    if (topLeft.y <= bottomLeft.y) throw -1;
    if (topLeft.x >= topRight.x) throw -2;
}

bool Rectangle::isOverlapping(const Rectangle &rectangle) const {
    // If one rectangle is on left side of other
    if (topLeft.x >= rectangle.bottomRight.x || bottomRight.x <= rectangle.topLeft.x) {
        return false;
    }

    // If one rectangle is above other
    if (topLeft.y <= rectangle.bottomRight.y || bottomRight.y >= rectangle.topLeft.y) {
        return false;
    }
    return true;
}

Point2D Rectangle::getTopLeft() {
    return this->topLeft;
}

Point2D Rectangle::getTopRight() {
    return this->topRight;
}

Point2D Rectangle::getBottomLeft() {
    return this->bottomLeft;
}

Point2D Rectangle::getBottomRight() {
    return this->bottomRight;
}

std::ostream &operator<<(ostream &stream, const Rectangle &rectangle) {
    stream << "top left: " << rectangle.topLeft << " | "
           << "top right: " << rectangle.topRight << " | "
           << "bottom left: " << rectangle.bottomLeft << " | "
           << "bottom right: " << rectangle.bottomRight << " | ";
    return stream;
}

