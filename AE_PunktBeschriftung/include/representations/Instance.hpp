#pragma once

#include <representations/Point.hpp>
#include <vector>

class Instance {

private:

    std::vector<Point> points; // contains all points of the instance

    std::vector<int> labelled_points; // contains all indices of points with actual labels

    friend std::ostream& operator<<(std::ostream &ostream, const Instance &instance);

public:

    Instance(int size);

    void reserve(int num);

    void add(const Point& point);

    int size() const;

    void setLabel(int idx, Point::Corner corner);

    const Point& getPoint(int idx) const;

    std::vector<int>& getLabelledPoints();

    int countLabelledPoints() const;

    bool isFeasible() const;
};

