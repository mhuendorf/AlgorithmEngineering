#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <memory>

class Point {

public:

    using Ptr = std::shared_ptr<Point>;
    using Point2D = std::tuple<long, long>;
    using Rectangle = std::tuple<Point2D, Point2D>;

    enum Corner {
        NOT_PLACED = 0, TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
    };

private:

    int idx;
    long x;
    long y;
    long width;
    long height;
    std::string label;

    std::vector<Point::Ptr> neighbours;

    friend std::ostream &operator<<(std::ostream &ostream, const Point &point);

public:

    Point(int idx, long x, long y, long width, long height, std::string label);

    int getIdx() const;

    long getX() const;

    long getY() const;

    std::string getName() const;

    Rectangle getBigRectangle() const;

    bool couldCollide(const Point& other) const;

    void addNeighbour(Point::Ptr other);

    const std::vector<Point::Ptr>& getNeighbours() const;

    Rectangle getCoordsForPlacement(Corner corner) const;

    static bool checkCollision(Rectangle rect1, Rectangle rect2);

};

