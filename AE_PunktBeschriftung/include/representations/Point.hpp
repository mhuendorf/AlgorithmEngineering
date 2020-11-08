#pragma once

#include <string>
#include <tuple>

using Point2D = std::tuple<int, int>;

class Point {

public:

    enum Corner {
        NOT_PLACED = 0, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
    };

private:

    int x;
    int y;
    int width;
    int height;
    std::string label;
    Corner placement;

    std::tuple<int, int> upperLeft;
    std::tuple<int, int> lowerRight;

    friend std::ostream &operator<<(std::ostream &ostream, const Point &point);

public:

    Point(int x, int y, int width, int height, std::string label);

    int getX() const;

    int getY() const;

    std::string getName() const;

    void setPlacement(Corner placement);

    bool checkCollision(const Point& other, Corner corner) const;

    std::tuple< Point2D, Point2D > getCoordsForPlacement(Corner corner) const;

};
