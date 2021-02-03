#pragma once

#include <string>
#include <tuple>
#include <vector>
#include <memory>

class Point {

public:

    using Ptr = std::shared_ptr<Point>;
    using Point2D = std::tuple<int, int>;
    using Rectangle = std::tuple<Point2D, Point2D>;

    enum Corner {
        TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, NOT_PLACED
    };

private:

    int idx;
    int x;
    int y;
    int width;
    int height;
    std::string label;

    std::vector<Point*> neighbours;

    friend std::ostream &operator<<(std::ostream &ostream, const Point &point);

public:

    Point(int idx, int x, int y, int width, int height, std::string label);

    int getIdx() const;

    int getX() const;

    int getY() const;

    std::string getName() const;

    Rectangle getBigRectangle() const;

    bool couldCollide(const Point& other) const;

    void addNeighbour(Point* other);

    const std::vector<Point*>& getNeighbours() const;

    Rectangle getCoordsForPlacement(Corner corner) const;

    static bool checkCollision(Rectangle rect1, Rectangle rect2);

};

