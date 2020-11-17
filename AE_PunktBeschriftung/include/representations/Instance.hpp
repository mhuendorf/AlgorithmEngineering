#pragma once

#include <representations/Point.hpp>
#include <vector>

class Instance {

private:

    std::vector<Point> points; // contains all points of the instance

    friend std::ostream &operator<<(std::ostream &ostream, const Instance &instance);

public:

    explicit Instance(int size);

    void reserve(int num);

    void setLabel(int idx, Point::Corner corner);

    void add(const Point &point);

    [[nodiscard]] int size() const;

    [[nodiscard]] const Point& getPoint(int idx) const;

};

