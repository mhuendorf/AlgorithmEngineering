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

    [[nodiscard]] int getX() const;

    [[nodiscard]] int getY() const;

    [[nodiscard]] std::string getName() const;

    void setPlacement(Corner placement) const;

    [[nodiscard]] const Corner &getPlacement() const;

    [[nodiscard]] bool checkCollision(const Point &other, Corner corner) const;

    [[nodiscard]] bool checkCollision(const Point &other) const;

    [[nodiscard]] std::tuple<Point2D, Point2D> getCoordsForPlacement(Corner corner) const;

};
