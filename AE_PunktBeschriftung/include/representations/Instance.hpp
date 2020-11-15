#pragma once

#include <representations/Point.hpp>
#include <vector>

class Instance {

private:

    std::vector<Point> points; // contains all points of the instance TODO should maybe be a map?

    friend std::ostream& operator<<(std::ostream &ostream, const Instance &instance);

public:

    Instance();
    
    Instance(int size);


    void reserve(int num);

    void add(Point& point);

    int size() const;

    const Point& getPoint(int idx) const;
};

