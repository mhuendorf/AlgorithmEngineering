#ifndef UNTITLED_RECTANGLE_HPP
#define UNTITLED_RECTANGLE_HPP

#include <iostream>
#include <representations/Point2D.hpp>

using namespace std;

class Rectangle {
private:
    const Point2D topLeft;
    const Point2D topRight;
    const Point2D bottomLeft;
    const Point2D bottomRight;

public:
    Rectangle(int x1, int y1, int x2, int y2);

    [[nodiscard]] bool isOverlapping(const Rectangle &rectangle) const;

    Point2D getTopLeft();

    Point2D getTopRight();

    Point2D getBottomLeft();

    Point2D getBottomRight();

    friend std::ostream &operator<<(std::ostream &stream, const Rectangle &rectangle);
};


#endif //UNTITLED_RECTANGLE_HPP
